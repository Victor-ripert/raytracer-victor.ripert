/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** raytracing
*/

#include <iostream>
#include <memory>
#include <string>
#include "Core/Render/Camera.hpp"
#include "Core/Scene/Scene.hpp"
#include "Core/Scene/SceneBuilder.hpp"
#include "Core/Render/Renderer.hpp"
#include "errors/IError.hpp"

int main(int argc, char **argv)
{
    constexpr int EXIT_OK = 0;
    constexpr int EXIT_ERROR = 84;
    
    if (argc != 2) {
        std::cerr << "USAGE: ./raytracer <SCENE.cfg>\n";
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

        // Build the scene from the config file
        RayTracer::SceneBuilder::build(argv[1], scene, camera, renderParams);

        // Core Rendering Refactor: Use the Renderer class
        RayTracer::Renderer renderer;
        renderer.render(scene, camera, renderParams);
        
        // Output Management: Save to file (defaulting to output.ppm for now)
        renderer.saveToFile("output.ppm");
        std::cout << "Render completed successfully. Image saved to output.ppm" << std::endl;

    } catch (const RayTracer::IError &error) {
        std::cerr << error.what() << std::endl;
        return EXIT_ERROR;
    } catch (const std::exception &error) {
        std::cerr << "Type: Unknown\nMessage: " << error.what() << std::endl;
        return EXIT_ERROR;
    }

    return EXIT_OK;
}
