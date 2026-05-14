/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** ConfigParse
*/

#include <algorithm>
#include <cctype>
#include <cmath>
#include <functional>
#include <optional>
#include <unordered_map>
#include "Core/Config/ConfigParse.hpp"
#include "Core/Render/Camera.hpp"
#include "errors/RayTracerErrors.hpp"

namespace {

    using PrimitiveConfigReader = RayTracer::PrimitiveConfig (*)(const libconfig::Setting &node);

    bool tryReadDouble(const libconfig::Setting &group, const char *key, double &valueOut)
    {
        int intValue = 0;
        if (group.lookupValue(key, intValue)) {
            valueOut = intValue;
            return true;
        }
        double doubleValue = 0;
        if (group.lookupValue(key, doubleValue)) {
            valueOut = doubleValue;
            return true;
        }
        return false;
    }

    RayTracer::PrimitiveConfig readSpherePrimitiveConfig(const libconfig::Setting &node)
    {
        RayTracer::PrimitiveConfig config{};

        if (node.exists("position"))
            config.position = RayTracer::ConfigParse::readPoint3(node["position"], "sphere.position");
        else if (node.exists("center"))
            config.position = RayTracer::ConfigParse::readPoint3(node["center"], "sphere.center");
        else
            throw RayTracer::ErrorConfig("sphere: missing position or center");

        if (!tryReadDouble(node, "radius", config.radius))
            tryReadDouble(node, "r", config.radius);

        if (node.exists("color"))
            config.color = RayTracer::ConfigParse::readRgbColor(node["color"], "sphere.color");

        if (node.exists("translation")) {
            math::Vector3D translation = RayTracer::ConfigParse::readVector3(node["translation"], "sphere.translation");
            config.position += translation;
        }
        return config;
    }

    RayTracer::PrimitiveConfig readPlanePrimitiveConfig(const libconfig::Setting &node)
    {
        RayTracer::PrimitiveConfig config{};

        config.position = RayTracer::ConfigParse::readPoint3(node["point"], "plane.point");
        config.normal = RayTracer::ConfigParse::readVector3(node["normal"], "plane.normal");
        if (node.exists("color"))
            config.color = RayTracer::ConfigParse::readRgbColor(node["color"], "plane.color");
        return config;
    }

    const std::unordered_map<std::string, PrimitiveConfigReader> PRIMITIVE_CONFIG_UMAP = {
        {"sphere", readSpherePrimitiveConfig},
        {"plane", readPlanePrimitiveConfig}
    };

}

namespace RayTracer {

    namespace ConfigParse {

        void readRenderResolution(const libconfig::Setting &cameraGroup, unsigned int &width, unsigned int &height)
        {
            if (!cameraGroup.exists("resolution"))
                throw ErrorConfig("camera: missing \"resolution\" group");
            const libconfig::Setting &resolution = cameraGroup["resolution"];
            int imageWidth = 0;
            int imageHeight = 0;
            if (!resolution.lookupValue("width", imageWidth) || !resolution.lookupValue("height", imageHeight))
                throw ErrorConfig("camera.resolution: width and height are required");
            if (imageWidth <= 0 || imageHeight <= 0)
                throw ErrorConfig("camera.resolution: width and height must be positive");
            width = static_cast<unsigned int>(imageWidth);
            height = static_cast<unsigned int>(imageHeight);
        }

        void applyCameraFromConfig(const libconfig::Setting &cameraGroup, Camera &camera)
        {
            if (cameraGroup.exists("position"))
                camera.origin = readPoint3(cameraGroup["position"], "camera.position");
            else if (cameraGroup.exists("origin"))
                camera.origin = readPoint3(cameraGroup["origin"], "camera.origin");

            double verticalFov = 72.0;
            double fovDouble = 0;
            int fovInt = 0;
            if (cameraGroup.lookupValue("fieldOfView", fovDouble))
                verticalFov = fovDouble;
            else if (cameraGroup.lookupValue("fov", fovDouble))
                verticalFov = fovDouble;
            else if (cameraGroup.lookupValue("fieldOfView", fovInt))
                verticalFov = static_cast<double>(fovInt);
            else if (cameraGroup.lookupValue("fov", fovInt))
                verticalFov = static_cast<double>(fovInt);
            camera.setVerticalFovDegrees(verticalFov);

            if (cameraGroup.exists("rotation"))
                camera.setRotationDegrees(readVector3(cameraGroup["rotation"], "camera.rotation"));
            else
                camera.setRotationDegrees(math::Vector3D(0, 0, 0));
        }

        std::optional<std::reference_wrapper<const libconfig::Setting>> optionalList(
            const libconfig::Setting &root, const char *key, const char *notListError)
        {
            if (!root.exists(key))
                return std::nullopt;
            const libconfig::Setting &list = root[key];
            if (list.getType() != libconfig::Setting::TypeList)
                throw ErrorConfig(notListError);
            return std::cref(list);
        }

        std::string toLower(std::string value)
        {
            std::transform(
                value.begin(),
                value.end(),
                value.begin(),
                [](unsigned char character) { return static_cast<char>(std::tolower(character)); });
            return value;
        }

        std::string readType(const libconfig::Setting &node, const char *contextLabel)
        {
            std::string typeValue;
            if (!node.lookupValue("type", typeValue))
                throw ErrorConfig(std::string(contextLabel) + ": missing string field \"type\"");
            return toLower(std::move(typeValue));
        }

        PrimitiveConfig readPrimitiveConfig(const std::string &typeName, const libconfig::Setting &node)
        {
            const std::string kind = toLower(typeName);

            const auto reader = PRIMITIVE_CONFIG_UMAP.find(kind);
            if (reader == PRIMITIVE_CONFIG_UMAP.end())
                throw ErrorConfig(std::string("Unknown primitive type: ") + typeName);
            return reader->second(node);
        }

        math::Vector3D readVector3(const libconfig::Setting &group, const char *contextLabel)
        {
            double x = 0;
            double y = 0;
            double z = 0;
            if (!tryReadDouble(group, "x", x) || !tryReadDouble(group, "y", y) || !tryReadDouble(group, "z", z))
                throw ErrorConfig(std::string(contextLabel) + ": expected numeric fields x, y, z");
            return math::Vector3D(x, y, z);
        }

        math::Point3D readPoint3(const libconfig::Setting &group, const char *contextLabel)
        {
            const math::Vector3D vector = readVector3(group, contextLabel);
            return math::Point3D(vector._x, vector._y, vector._z);
        }

        Color readRgbColor(const libconfig::Setting &group, const char *contextLabel)
        {
            double red = 0;
            double green = 0;
            double blue = 0;
            if (!tryReadDouble(group, "r", red) || !tryReadDouble(group, "g", green) || !tryReadDouble(group, "b", blue))
                throw ErrorConfig(std::string(contextLabel) + ": color must define r, g, b");
            const double maxChannel = std::max(red, std::max(green, blue));
            if (maxChannel > 1.0) {
                red /= 255.0;
                green /= 255.0;
                blue /= 255.0;
            }
            red = std::clamp(red, 0.0, 1.0);
            green = std::clamp(green, 0.0, 1.0);
            blue = std::clamp(blue, 0.0, 1.0);
            return Color(
                static_cast<size_t>(std::lround(red * 255.0)),
                static_cast<size_t>(std::lround(green * 255.0)),
                static_cast<size_t>(std::lround(blue * 255.0)));
        }

    }

}
