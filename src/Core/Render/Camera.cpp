/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracing
*/

#include "Core/Render/Camera.hpp"

namespace RayTracer {
    Camera::Camera() {
        origin = math::Point3D();
        screen = Rectangle3D();
    }

    Ray Camera::ray(double u, double v) {
        math::Point3D pixel = screen.pointAt(u, v);
        math::Vector3D direction = pixel - origin;
        return Ray(origin, direction);
    }
}