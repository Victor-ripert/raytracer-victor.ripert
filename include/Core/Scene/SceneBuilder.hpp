/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** SceneBuilder — libconfig scene -> Scene + Camera
*/

#ifndef RAYTRACER_SCENEBUILDER_HPP
#define RAYTRACER_SCENEBUILDER_HPP

#include <string>
#include "Core/Render/Camera.hpp"
#include "Core/Scene/Scene.hpp"

namespace RayTracer {

    /**
     * @brief Structure to hold global rendering settings.
     */
    struct RenderParams {
        unsigned int width = 800;  /**< Output image width */
        unsigned int height = 600; /**< Output image height */
    };

    /**
     * @brief Utility class to construct a Scene and Camera from a configuration file.
     */
    class SceneBuilder {
        public:
            /**
             * @brief Parse a .cfg file and populate the scene and camera objects.
             * 
             * @param scenePath Path to the libconfig file.
             * @param scene The Scene object to populate with primitives and lights.
             * @param camera The Camera object to configure.
             * @param params Output parameters (resolution, etc.) to set.
             */
            static void build(const std::string &scenePath, Scene &scene, Camera &camera, RenderParams &params);
    };

}

#endif /* RAYTRACER_SCENEBUILDER_HPP */
