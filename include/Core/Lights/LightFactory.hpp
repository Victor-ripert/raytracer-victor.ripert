/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** LightFactory
*/

#ifndef RAYTRACER_LIGHTFACTORY_HPP
#define RAYTRACER_LIGHTFACTORY_HPP

#include <libconfig.h++>
#include <memory>
#include <string>
#include "API/ILight.hpp"

namespace RayTracer {

    class LightFactory {
        public:
            LightFactory() = default;
            ~LightFactory() = default;

            LightFactory(const LightFactory &) = delete;
            LightFactory &operator=(const LightFactory &) = delete;

            std::shared_ptr<ILight> create(const std::string &typeName, const libconfig::Setting &node) const;
    };

}

#endif /* RAYTRACER_LIGHTFACTORY_HPP */
