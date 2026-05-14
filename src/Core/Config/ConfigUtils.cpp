/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** ConfigUtils
*/

#include <algorithm>
#include <cctype>
#include <cmath>
#include "Core/Config/ConfigUtils.hpp"
#include "errors/RayTracerErrors.hpp"

namespace RayTracer {
    namespace ConfigUtils {
        std::string toLower(std::string value) {
            std::transform(value.begin(), value.end(), value.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            return value;
        }

        bool tryReadDouble(const libconfig::Setting &group, const char *key, double &valueOut) {
            int intValue = 0;
            if (group.lookupValue(key, intValue)) {
                valueOut = static_cast<double>(intValue);
                return true;
            }
            if (group.lookupValue(key, valueOut)) {
                return true;
            }
            return false;
        }

        math::Vector3D readVector3(const libconfig::Setting &group) {
            double x = 0, y = 0, z = 0;
            if (!tryReadDouble(group, "x", x) || !tryReadDouble(group, "y", y) || !tryReadDouble(group, "z", z))
                throw ErrorConfig("Expected numeric fields x, y, z");
            return math::Vector3D(x, y, z);
        }

        math::Point3D readPoint3(const libconfig::Setting &group) {
            const math::Vector3D v = readVector3(group);
            return math::Point3D(v._x, v._y, v._z);
        }

        Color readColor(const libconfig::Setting &group) {
            double r = 0, g = 0, b = 0;
            if (!tryReadDouble(group, "r", r) || !tryReadDouble(group, "g", g) || !tryReadDouble(group, "b", b))
                throw ErrorConfig("Color must define r, g, b");
            
            if (r > 1.0 || g > 1.0 || b > 1.0) {
                return Color(static_cast<size_t>(r), static_cast<size_t>(g), static_cast<size_t>(b));
            }
            return Color(static_cast<size_t>(r * 255), static_cast<size_t>(g * 255), static_cast<size_t>(b * 255));
        }

        std::optional<std::reference_wrapper<const libconfig::Setting>> optionalList(const libconfig::Setting &root, const char *key) {
            if (!root.exists(key))
                return std::nullopt;
            const libconfig::Setting &list = root[key];
            if (list.getType() != libconfig::Setting::TypeList)
                throw ErrorConfig(std::string(key) + " must be a list");
            return std::cref(list);
        }
    }
}
