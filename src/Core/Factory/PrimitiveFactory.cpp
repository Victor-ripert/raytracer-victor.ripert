/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** PrimitiveFactory
*/

#include "Core/Factory/PrimitiveFactory.hpp"
#include "Core/Config/ConfigParse.hpp"
#include "Core/Factory/PluginLoader.hpp"
#include "errors/RayTracerErrors.hpp"

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

    PrimitiveConfig PrimitiveFactory::parseSphereLike(const libconfig::Setting &node)
    {
        PrimitiveConfig config{};
        if (node.exists("position")) {
            config.position = ConfigParse::readPoint3(node["position"], "sphere.position");
        } else if (node.exists("center")) {
            config.position = ConfigParse::readPoint3(node["center"], "sphere.center");
        } else {
            throw ErrorConfig("sphere: missing position or center");
        }
        config.radius = 1.0;
        double radiusDouble = 0;
        int radiusInt = 0;
        if (node.lookupValue("radius", radiusDouble)) {
            config.radius = radiusDouble;
        } else if (node.lookupValue("r", radiusDouble)) {
            config.radius = radiusDouble;
        } else if (node.lookupValue("radius", radiusInt)) {
            config.radius = radiusInt;
        } else if (node.lookupValue("r", radiusInt)) {
            config.radius = radiusInt;
        }
        if (node.exists("color")) {
            config.color = ConfigParse::readRgbColor(node["color"], "sphere.color");
        }
        return config;
    }

    PrimitiveConfig PrimitiveFactory::parsePlaneLike(const libconfig::Setting &node)
    {
        PrimitiveConfig config{};
        config.position = ConfigParse::readPoint3(node["point"], "plane.point");
        config.normal = ConfigParse::readVector3(node["normal"], "plane.normal");
        if (node.exists("color")) {
            config.color = ConfigParse::readRgbColor(node["color"], "plane.color");
        }
        return config;
    }

    std::shared_ptr<IPrimitive> PrimitiveFactory::create(const std::string &typeName, const libconfig::Setting &node) const
    {
        const std::string kind = ConfigParse::toLower(typeName);
        std::string sharedObject;
        PrimitiveConfig configuration{};

        if (kind == "sphere") {
            sharedObject = joinPath(_pluginDirectory, "sphere.so");
            configuration = parseSphereLike(node);
        } else if (kind == "plane") {
            sharedObject = joinPath(_pluginDirectory, "plane.so");
            configuration = parsePlaneLike(node);
        } else {
            throw ErrorConfig(std::string("Unknown primitive type: ") + typeName);
        }

        std::shared_ptr<IPrimitive> primitive = PluginLoader::load<IPrimitive>(sharedObject, "create_primitive");
        primitive->applyConfig(configuration);
        return primitive;
    }

}
