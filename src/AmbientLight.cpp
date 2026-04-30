/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracing
*/

#include "../include/AmbientLight.hpp"

namespace RayTracer {
    AmbientLight::AmbientLight() {
        origin = math::Point3D();
    }

    AmbientLight::AmbientLight(math::Point3D point) : origin(point) {}

    Ray AmbientLight::ray(math::Point3D point) {
        math::Vector3D direction;

        direction = point - origin;
        return Ray(origin, direction);
    }
}
