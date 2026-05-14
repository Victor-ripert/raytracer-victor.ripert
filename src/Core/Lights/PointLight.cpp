/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** PointLight
*/

#include "Core/Lights/PointLight.hpp"

namespace RayTracer {
    PointLight::PointLight() : origin(math::Point3D(0, 0, 0)) {}

    PointLight::PointLight(math::Point3D point) : origin(point) {}

    Ray PointLight::getRayToLight(const math::Point3D &point) const {
        math::Vector3D direction = origin - point;
        return Ray(point, direction);
    }

    double PointLight::getDistanceToLight(const math::Point3D &point) const {
        return origin.distance_point(point);
    }

    math::Point3D PointLight::getPosition() const {
        return origin;
    }

    math::Vector3D PointLight::vectorSurfaceToLight(const math::Point3D &surface) const
    {
        math::Vector3D toward(origin - surface);
        toward.normalize();
        return toward;
    }

    bool PointLight::isInLigthningWidth(const math::Vector3D ray_to_light_vector) const { // I have to change my code, because this type of light don't need this function.
        if (ray_to_light_vector.length() != 0) // This is bullshit to avoid compilation error, i'm going to erase it don't worry
            return true;
        return true;
    }
}
