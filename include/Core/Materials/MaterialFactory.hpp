/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** MaterialFactory
*/

#ifndef RAYTRACER_MATERIALFACTORY_HPP
#define RAYTRACER_MATERIALFACTORY_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include "API/IMaterial.hpp"
#include "Core/Factory/PluginLoader.hpp"

namespace RayTracer {

    class MaterialFactory {
        public:
            explicit MaterialFactory(std::string pluginDirectory);
            ~MaterialFactory();

            MaterialFactory(const MaterialFactory &) = delete;
            MaterialFactory &operator=(const MaterialFactory &) = delete;

            std::shared_ptr<IMaterial> create(const std::string &typeName, const libconfig::Setting &configuration) const;

        private:
            std::string _pluginDirectory;
            std::unordered_map<std::string, PluginSymbols<IMaterial>> _plugins;
    };

}

#endif /* RAYTRACER_MATERIALFACTORY_HPP */
