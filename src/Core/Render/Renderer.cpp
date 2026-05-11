/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** Renderer
*/

#include <fstream>
#include <iostream>
#include "Core/Render/Renderer.hpp"

namespace RayTracer {

    void Renderer::render(Scene &scene, Camera &camera, const RenderParams &params)
    {
        _width = params.width;
        _height = params.height;
        _pixels.assign(_height, std::vector<Color>(_width));

        for (unsigned int y = 0; y < _height; ++y) {
            for (unsigned int x = 0; x < _width; ++x) {
                const double u = static_cast<double>(x) / static_cast<double>(_width - 1);
                const double v = static_cast<double>(y) / static_cast<double>(_height - 1);
                const Ray ray = camera.ray(u, v);
                _pixels[y][x] = scene.hit_object(ray);
            }
        }
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
