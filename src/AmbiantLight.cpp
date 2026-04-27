/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracing
*/

#include "../include/AmbientLight.hpp"

namespace RayTracer {
    AmbiantLight::AmbiantLight() {
        origin = math::Point3D();
    }

    AmbiantLight::AmbiantLight(math::Point3D point) : origin(point) {}

    Ray AmbiantLight::ray(math::Point3D point) {
        math::Vector3D direction = point - origin;
        return Ray(origin, direction);
    }
}