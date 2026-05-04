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

    struct RenderParams {
        unsigned int width = 800;
        unsigned int height = 600;
    };

    class SceneBuilder {
        public:
            static void build(const std::string &scenePath, Scene &scene, Camera &camera, RenderParams &params);
    };

}

#endif /* RAYTRACER_SCENEBUILDER_HPP */
