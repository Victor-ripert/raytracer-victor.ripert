/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** Renderer
*/

#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <iomanip>
#include "Core/Render/Renderer.hpp"
#include "Core/Constants.hpp"

namespace RayTracer {

    void Renderer::render(const Scene &scene, Camera &camera, const RenderParams &params)
    {
        _width = params.width;
        _height = params.height;
        _pixels.assign(_height, std::vector<Color>(_width));

        unsigned int numThreads = std::thread::hardware_concurrency();
        if (numThreads == 0) numThreads = 1;

        std::vector<std::thread> threads;
        std::atomic<unsigned int> completedRows(0);
        unsigned int rowsPerThread = _height / numThreads;

        std::cout << "Rendering with " << numThreads << " threads..." << std::endl;

        for (unsigned int i = 0; i < numThreads; ++i) {
            unsigned int startY = i * rowsPerThread;
            unsigned int endY = (i == numThreads - 1) ? _height : (i + 1) * rowsPerThread;
            threads.emplace_back(&Renderer::renderRows, this, std::ref(scene), std::ref(camera), startY, endY, std::ref(completedRows));
        }

        for (auto &t : threads) {
            t.join();
        }
    }

    void Renderer::renderRows(const Scene &scene, Camera &camera, unsigned int startY, unsigned int endY, std::atomic<unsigned int> &completedRows)
    {
        for (unsigned int y = startY; y < endY; ++y) {
            for (unsigned int x = 0; x < _width; ++x) {
                const double u = static_cast<double>(x) / static_cast<double>(_width - 1);
                const double v = static_cast<double>(y) / static_cast<double>(_height - 1);
                const Ray ray = camera.ray(u, v);
                _pixels[y][x] = calculateColor(scene, ray);
            }
            completedRows++;
        }
    }

    Color Renderer::calculateColor(const Scene &scene, const Ray &ray) const
    {
        HitRecord record;
        if (!scene.closestHit(ray, EPSILON, INF, record)) {
            return Color(0, 0, 0);
        }

        const auto &lights = scene.getLights();
        if (lights.empty()) {
            return record.color;
        }

        Color finalColor(0, 0, 0);
        double totalIntensity = 0.0;

        for (const auto &light : lights) {
            if (!isInShadow(scene, light, record.hit_point)) {
                totalIntensity += getLightIntensity(light, record.hit_point, record.normal);
            }
        }

        double ambient = 0.2;
        double intensity = std::min(1.0, ambient + totalIntensity);
        
        Color shadedColor = record.color;
        shadedColor.setShade(intensity);
        return shadedColor;
    }

    bool Renderer::isInShadow(const Scene &scene, const std::shared_ptr<ILight> &light, const math::Point3D &point) const
    {
        Ray rayToLight = light->getRayToLight(point);
        double distanceToLight = light->getDistanceToLight(point);
        HitRecord tempRecord;

        return scene.closestHit(rayToLight, EPSILON, distanceToLight - EPSILON, tempRecord);
    }

    double Renderer::getLightIntensity(const std::shared_ptr<ILight> &light, const math::Point3D &point, const math::Vector3D &normal) const
    {
        math::Vector3D lightDir = light->vectorSurfaceToLight(point).normalize();
        double dot = normal.dot(lightDir);
        return std::max(0.0, dot);
    }

    void Renderer::saveToFile(const std::string &filename) const
    {
        std::ofstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Renderer: Could not open file for writing: " + filename);
        }

        file << "P3\n" << _width << ' ' << _height << "\n255\n";

        for (unsigned int y = 0; y < _height; ++y) {
            for (unsigned int x = 0; x < _width; ++x) {
                file << _pixels[y][x].to_str() << "\n";
            }
        }
        file.close();
    }

}
