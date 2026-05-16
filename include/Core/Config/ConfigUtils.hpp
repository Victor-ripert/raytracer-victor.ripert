/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** ConfigUtils
*/

#ifndef RAYTRACER_CONFIGUTILS_HPP
#define RAYTRACER_CONFIGUTILS_HPP

#include <libconfig.h++>
#include <string>
#include <optional>
#include <functional>
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Core/Render/Color.hpp"

namespace RayTracer {
    /**
     * @brief Helper functions for parsing libconfig settings.
     */
    namespace ConfigUtils {
        /** @brief Convert a string to lowercase. */
        std::string toLower(std::string value);
        
        /** @brief Try to read a double from a setting, handling both float and int types. */
        bool tryReadDouble(const libconfig::Setting &group, const char *key, double &valueOut);
        
        /** @brief Read a Vector3D from a setting group (x, y, z). */
        math::Vector3D readVector3(const libconfig::Setting &group);
        /** @brief Read a Point3D from a setting group (x, y, z). */
        math::Point3D readPoint3(const libconfig::Setting &group);
        /** @brief Read a Color from a setting group (r, g, b). */
        Color readColor(const libconfig::Setting &group);
        
        /** @brief Safely retrieve an optional list/array from a setting. */
        std::optional<std::reference_wrapper<const libconfig::Setting>> optionalList(const libconfig::Setting &root, const char *key);
    }
}

#endif /* RAYTRACER_CONFIGUTILS_HPP */
