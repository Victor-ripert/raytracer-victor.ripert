/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** ConfigParse — libconfig helpers
*/

#ifndef RAYTRACER_CONFIGPARSE_HPP
#define RAYTRACER_CONFIGPARSE_HPP

#include <libconfig.h++>
#include <string>
#include "Core/Render/Color.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

namespace RayTracer {

    namespace ConfigParse {

        std::string toLower(std::string value);
        std::string readType(const libconfig::Setting &node, const char *contextLabel);

        math::Point3D readPoint3(const libconfig::Setting &group, const char *contextLabel);
        math::Vector3D readVector3(const libconfig::Setting &group, const char *contextLabel);
        Color readRgbColor(const libconfig::Setting &group, const char *contextLabel);

    }

}

#endif /* RAYTRACER_CONFIGPARSE_HPP */
