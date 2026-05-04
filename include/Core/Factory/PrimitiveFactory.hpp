/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** PrimitiveFactory — load plugin + apply libconfig node
*/

#ifndef RAYTRACER_PRIMITIVEFACTORY_HPP
#define RAYTRACER_PRIMITIVEFACTORY_HPP

#include <libconfig.h++>
#include <memory>
#include <string>
#include "API/IPrimitive.hpp"

namespace RayTracer {

    class PrimitiveFactory {
        public:
            explicit PrimitiveFactory(std::string pluginDirectory);
            ~PrimitiveFactory() = default;

            PrimitiveFactory(const PrimitiveFactory &) = delete;
            PrimitiveFactory &operator=(const PrimitiveFactory &) = delete;

            std::shared_ptr<IPrimitive> create(const std::string &typeName, const libconfig::Setting &node) const;

        private:
            std::string _pluginDirectory;

            static std::string joinPath(const std::string &directory, const std::string &filename);
            static PrimitiveConfig parseSphereLike(const libconfig::Setting &node);
            static PrimitiveConfig parsePlaneLike(const libconfig::Setting &node);
    };

}

#endif /* RAYTRACER_PRIMITIVEFACTORY_HPP */
