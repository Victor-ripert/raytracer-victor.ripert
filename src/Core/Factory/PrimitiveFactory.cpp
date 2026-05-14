/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** PrimitiveFactory
*/

#include <filesystem>
#include <iostream>
#include "Core/Factory/PrimitiveFactory.hpp"
#include "Core/Factory/PluginLoader.hpp"
#include "errors/RayTracerErrors.hpp"

namespace RayTracer {

    PrimitiveFactory::PrimitiveFactory(std::string pluginDirectory) : _pluginDirectory(std::move(pluginDirectory))
    {
        if (!std::filesystem::exists(_pluginDirectory) || !std::filesystem::is_directory(_pluginDirectory)) {
            return;
        }

        for (const auto &entry : std::filesystem::directory_iterator(_pluginDirectory)) {
            if (entry.path().extension() == ".so") {
                try {
                    auto symbols = PluginLoader::load<IPrimitive>(entry.path().string(), "create_primitive", "destroy_primitive", "get_type");
                    std::string type = symbols.getType();
                    _plugins[type] = std::move(symbols);
                } catch (const ErrorPlugin &e) {
                    std::cerr << "PrimitiveFactory: Failed to load plugin " << entry.path() << ": " << e.what() << std::endl;
                }
            }
        }
    }

    PrimitiveFactory::~PrimitiveFactory() = default;

    std::shared_ptr<IPrimitive> PrimitiveFactory::create(const std::string &typeName, const libconfig::Setting &configuration) const
    {
        auto it = _plugins.find(typeName);
        if (it == _plugins.end()) {
            throw ErrorConfig(std::string("Unknown primitive type: ") + typeName);
        }

        const auto &symbols = it->second;
        IPrimitive *instance = symbols.create();
        if (!instance) {
            throw ErrorPlugin("PrimitiveFactory: Factory returned null for " + typeName);
        }

        auto shared_primitive = std::shared_ptr<IPrimitive>(instance, [symbols](IPrimitive *ptr) {
            symbols.destroy(ptr);
        });

        shared_primitive->applyConfig(configuration);
        return shared_primitive;
    }

}
