/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** MaterialFactory
*/

#include <filesystem>
#include <iostream>
#include "Core/Materials/MaterialFactory.hpp"
#include "Core/Factory/PluginLoader.hpp"
#include "errors/RayTracerErrors.hpp"

namespace RayTracer {

    MaterialFactory::MaterialFactory(std::string pluginDirectory) : _pluginDirectory(std::move(pluginDirectory))
    {
        if (!std::filesystem::exists(_pluginDirectory) || !std::filesystem::is_directory(_pluginDirectory)) {
            return;
        }

        for (const auto &entry : std::filesystem::directory_iterator(_pluginDirectory)) {
            if (entry.path().extension() == ".so") {
                try {
                    auto symbols = PluginLoader::load<IMaterial>(entry.path().string(), "create_material", "destroy_material", "get_type");
                    std::string type = symbols.getType();
                    _plugins[type] = std::move(symbols);
                } catch (const ErrorPlugin &e) {
                    std::cerr << "MaterialFactory: Failed to load plugin " << entry.path() << ": " << e.what() << std::endl;
                }
            }
        }
    }

    MaterialFactory::~MaterialFactory() = default;

    std::shared_ptr<IMaterial> MaterialFactory::create(const std::string &typeName, const libconfig::Setting &configuration) const
    {
        auto it = _plugins.find(typeName);
        if (it == _plugins.end()) {
            throw ErrorConfig(std::string("Unknown material type: ") + typeName);
        }

        const auto &symbols = it->second;
        IMaterial *instance = symbols.create();
        if (!instance) {
            throw ErrorPlugin("MaterialFactory: Factory returned null for " + typeName);
        }

        auto shared_material = std::shared_ptr<IMaterial>(instance, [symbols](IMaterial *ptr) {
            symbols.destroy(ptr);
        });

        shared_material->applyConfig(configuration);
        return shared_material;
    }

}
