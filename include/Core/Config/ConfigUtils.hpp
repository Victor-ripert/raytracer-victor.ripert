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
    namespace ConfigUtils {
        std::string toLower(std::string value);
        
        bool tryReadDouble(const libconfig::Setting &group, const char *key, double &valueOut);
        
        math::Vector3D readVector3(const libconfig::Setting &group);
        math::Point3D readPoint3(const libconfig::Setting &group);
        Color readColor(const libconfig::Setting &group);
        
        std::optional<std::reference_wrapper<const libconfig::Setting>> optionalList(const libconfig::Setting &root, const char *key);
    }
}

#endif /* RAYTRACER_CONFIGUTILS_HPP */
