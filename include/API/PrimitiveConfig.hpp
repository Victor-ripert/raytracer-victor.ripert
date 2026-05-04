/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** PrimitiveConfig — values parsed from libconfig for plugin primitives
*/

#ifndef RAYTRACER_PRIMITIVECONFIG_HPP
#define RAYTRACER_PRIMITIVECONFIG_HPP

#include "Core/Color.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

namespace RayTracer {

    struct PrimitiveConfig {
        math::Point3D position{};
        math::Vector3D normal{0, 1, 0};
        double radius = 1.0;
        Color color{128, 128, 128};
    };

}

#endif /* RAYTRACER_PRIMITIVECONFIG_HPP */
