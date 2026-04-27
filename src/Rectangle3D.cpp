/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Raytracer
*/


#include "../include/Rectangle3D.hpp"

namespace RayTracer {
    Rectangle3D::Rectangle3D() {
        origin = math::Point3D(-1, -0.75, -1);
        bottom_side = math::Vector3D(2, 0, 0);
        left_side = math::Vector3D(0, 1.5, 0);
    }

    math::Point3D Rectangle3D::pointAt(double u, double v) {
        return origin + (bottom_side * u) + (left_side * v);
    }
}