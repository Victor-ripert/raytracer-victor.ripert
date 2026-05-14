/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** PrimitiveFactory
*/

#ifndef RAYTRACER_PRIMITIVEFACTORY_HPP
#define RAYTRACER_PRIMITIVEFACTORY_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include "API/IPrimitive.hpp"
#include "PluginLoader.hpp"

namespace RayTracer {

    class PrimitiveFactory {
        public:
            explicit PrimitiveFactory(std::string pluginDirectory);
            ~PrimitiveFactory();

            PrimitiveFactory(const PrimitiveFactory &) = delete;
            PrimitiveFactory &operator=(const PrimitiveFactory &) = delete;

            std::shared_ptr<IPrimitive> create(const std::string &typeName, const libconfig::Setting &configuration) const;

        private:
            std::string _pluginDirectory;
            std::unordered_map<std::string, PluginSymbols<IPrimitive>> _plugins;
    };

}

#endif /* RAYTRACER_PRIMITIVEFACTORY_HPP */
