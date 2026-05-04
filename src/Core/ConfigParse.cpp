/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** ConfigParse
*/

#include <algorithm>
#include <cctype>
#include <cmath>
#include "Core/ConfigParse.hpp"
#include "errors/RayTracerErrors.hpp"

namespace {

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

}

namespace RayTracer {

    namespace ConfigParse {

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
            if (!node.lookupValue("type", typeValue)) {
                throw ErrorConfig(std::string(contextLabel) + ": missing string field \"type\"");
            }
            return toLower(std::move(typeValue));
        }

        math::Vector3D readVector3(const libconfig::Setting &group, const char *contextLabel)
        {
            double x = 0;
            double y = 0;
            double z = 0;
            if (!tryReadDouble(group, "x", x) || !tryReadDouble(group, "y", y) || !tryReadDouble(group, "z", z)) {
                throw ErrorConfig(std::string(contextLabel) + ": expected numeric fields x, y, z");
            }
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
            if (!tryReadDouble(group, "r", red) || !tryReadDouble(group, "g", green) || !tryReadDouble(group, "b", blue)) {
                throw ErrorConfig(std::string(contextLabel) + ": color must define r, g, b");
            }
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
