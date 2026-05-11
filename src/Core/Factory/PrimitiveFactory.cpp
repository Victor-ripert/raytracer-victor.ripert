/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** PrimitiveFactory
*/

#include <unordered_map>
#include "Core/Factory/PrimitiveFactory.hpp"
#include "Core/Factory/PluginLoader.hpp"
#include "errors/RayTracerErrors.hpp"

static const std::unordered_map<std::string, std::string> PRIMITIVE_PLUGINS = {
    {"sphere", "sphere.so"},
    {"plane", "plane.so"}
};

namespace RayTracer {

    PrimitiveFactory::PrimitiveFactory(std::string pluginDirectory) : _pluginDirectory(std::move(pluginDirectory)) {}

    std::string PrimitiveFactory::joinPath(const std::string &directory, const std::string &filename)
    {
        if (directory.empty())
            return filename;
        if (!directory.empty() && directory.back() == '/')
            return directory + filename;
        return directory + "/" + filename;
    }

    std::shared_ptr<IPrimitive> PrimitiveFactory::create(const std::string &typeName, const PrimitiveConfig &configuration) const
    {
        const auto plugin = PRIMITIVE_PLUGINS.find(typeName);
        if (plugin == PRIMITIVE_PLUGINS.end()) {
            throw ErrorConfig(std::string("Unknown primitive type: ") + typeName);
        }
        const std::string sharedObject = joinPath(_pluginDirectory, plugin->second);
        std::shared_ptr<IPrimitive> primitive = PluginLoader::load<IPrimitive>(sharedObject, "create_primitive");
        primitive->applyConfig(configuration);
        return primitive;
    }

}
