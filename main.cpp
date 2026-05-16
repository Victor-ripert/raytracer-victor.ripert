/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** raytracing
*/

#include <iostream>
#include <memory>
#include <string>
#include <filesystem>
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
    std::string configPath(argv[1]);
    if (configPath == "--help" || configPath == "-h") {
        std::cout << "USAGE: ./raytracer <SCENE.cfg>\n";
        return EXIT_OK;
    }

    try {
        RayTracer::Scene scene;
        RayTracer::Camera camera;
        RayTracer::RenderParams renderParams;

        // Build the scene from the config file
        RayTracer::SceneBuilder::build(configPath, scene, camera, renderParams);

        // Core Rendering Refactor: Use the Renderer class
        RayTracer::Renderer renderer;
        renderer.render(scene, camera, renderParams);
        
        // Output Management: Save to screenshots/ folder with config filename
        std::filesystem::path p(configPath);
        std::string filename = p.stem().string() + ".ppm";
        std::filesystem::path outputDir("screenshots");
        
        if (!std::filesystem::exists(outputDir)) {
            std::filesystem::create_directory(outputDir);
        }
        
        std::filesystem::path outputPath = outputDir / filename;
        renderer.saveToFile(outputPath.string());
        std::cout << "Render completed successfully. Image saved to " << outputPath.string() << std::endl;

    } catch (const RayTracer::IError &error) {
        std::cerr << error.what() << std::endl;
        return EXIT_ERROR;
    } catch (const std::exception &error) {
        std::cerr << "Type: Unknown\nMessage: " << error.what() << std::endl;
        return EXIT_ERROR;
    }

    return EXIT_OK;
}
