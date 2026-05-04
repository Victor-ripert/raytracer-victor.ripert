/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** raytracing_bootstrap
*/

#include <iostream>
#include <memory>
#include <string>
#include "Core/Render/Camera.hpp"
#include "Core/Scene/Scene.hpp"
#include "Core/Scene/SceneBuilder.hpp"
#include "errors/IError.hpp"

int main(int argc, char **argv)
{
    constexpr int EXIT_OK = 0;
    constexpr int EXIT_ERROR = 84;
    
    if (argc != 2) {
        std::cout << "USAGE: ./raytracer <SCENE.cfg>\n";
        return EXIT_ERROR;
    }
    if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
        std::cout << "USAGE: ./raytracer <SCENE.cfg>\n";
        return EXIT_OK;
    }

    try {
        RayTracer::Scene scene;
        RayTracer::Camera camera;
        RayTracer::RenderParams renderParams;

        RayTracer::SceneBuilder::build(argv[1], scene, camera, renderParams);

        std::cout << "P3\n" << renderParams.width << ' ' << renderParams.height << "\n255\n";

        for (unsigned int y = 0; y < renderParams.height; ++y) {
            for (unsigned int x = 0; x < renderParams.width; ++x) {
                const double u = static_cast<double>(x) / static_cast<double>(renderParams.width - 1);
                const double v = static_cast<double>(y) / static_cast<double>(renderParams.height - 1);
                const RayTracer::Ray ray = camera.ray(u, v);
                scene.hit_object(ray);
            }
        }
    } catch (const RayTracer::IError &error) {
        std::cerr << error.what() << std::endl;
        return EXIT_ERROR;
    } catch (const std::exception &error) {
        std::cerr << "Type: Unknown\nMessage: " << error.what() << std::endl;
        return EXIT_ERROR;
    }

    return EXIT_OK;
}
