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

            void render(const Scene &scene, Camera &camera, const RenderParams &params);
            void saveToFile(const std::string &filename) const;

        private:
            Color calculateColor(const Scene &scene, const Ray &ray) const;
            bool isInShadow(const Scene &scene, const std::shared_ptr<ILight> &light, const math::Point3D &point) const;
            double getLightIntensity(const std::shared_ptr<ILight> &light, const math::Point3D &point, const math::Vector3D &normal) const;

            std::vector<std::vector<Color>> _pixels;
            unsigned int _width = 0;
            unsigned int _height = 0;
    };

}

#endif /* RAYTRACER_RENDERER_HPP */
