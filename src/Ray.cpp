/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracer bootstrap
*/


#include "../include/Ray.hpp"

namespace RayTracer {
    Ray::Ray() {
        _origin = math::Point3D();
        _direction = math::Vector3D();
    }

    Ray::Ray(math::Point3D origin, math::Vector3D direction) : _origin(origin), _direction(direction) {}
}