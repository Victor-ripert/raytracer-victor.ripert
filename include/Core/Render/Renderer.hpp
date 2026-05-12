/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** Renderer
*/

#ifndef RAYTRACER_RENDERER_HPP
#define RAYTRACER_RENDERER_HPP

#include <string>
#include <vector>
#include "Core/Scene/Scene.hpp"
#include "Core/Render/Camera.hpp"
#include "Core/Render/Color.hpp"
#include "Core/Scene/SceneBuilder.hpp"

namespace RayTracer {

    /**
     * @brief The Renderer class handles the rendering process and output management.
     */
    class Renderer {
        public:
            Renderer() = default;
            ~Renderer() = default;

            /**
             * @brief Renders the scene from the camera's perspective.
             * 
             * @param scene The scene to render.
             * @param camera The camera to use.
             * @param params The rendering parameters (resolution).
             */
            void render(Scene &scene, Camera &camera, const RenderParams &params);

            /**
             * @brief Saves the rendered image to a PPM file.
             * 
             * @param filename The name of the file to save.
             */
            void saveToFile(const std::string &filename) const;

        private:
            std::vector<std::vector<Color>> _pixels;
            unsigned int _width = 0;
            unsigned int _height = 0;
    };

}

#endif /* RAYTRACER_RENDERER_HPP */
