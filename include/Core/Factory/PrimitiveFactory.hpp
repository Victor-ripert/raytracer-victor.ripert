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

    /**
     * @brief Factory class to manage and create primitives from dynamic plugins.
     * 
     * It scans a directory for .so files, loads them as plugins, and maps
     * their type names to their respective creation functions.
     */
    class PrimitiveFactory {
        public:
            /**
             * @brief Construct a new Primitive Factory.
             * @param pluginDirectory Path to the directory containing .so plugins.
             */
            explicit PrimitiveFactory(std::string pluginDirectory);
            ~PrimitiveFactory();

            // Disable copying
            PrimitiveFactory(const PrimitiveFactory &) = delete;
            PrimitiveFactory &operator=(const PrimitiveFactory &) = delete;

            /**
             * @brief Create a new primitive instance based on its type name.
             * 
             * @param typeName The type identifier (e.g., "sphere").
             * @param configuration The libconfig node to initialize the primitive.
             * @return std::shared_ptr<IPrimitive> A pointer to the new instance.
             */
            std::shared_ptr<IPrimitive> create(const std::string &typeName, const libconfig::Setting &configuration) const;

        private:
            std::string _pluginDirectory;
            std::unordered_map<std::string, PluginSymbols<IPrimitive>> _plugins;
    };

}

#endif /* RAYTRACER_PRIMITIVEFACTORY_HPP */
