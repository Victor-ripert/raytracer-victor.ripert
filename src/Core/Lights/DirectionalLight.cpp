/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** DirectionalLight
*/

#include "Core/Lights/DirectionalLight.hpp"

namespace RayTracer {

    DirectionalLight::DirectionalLight() = default;

    DirectionalLight::DirectionalLight(math::Vector3D towardLightVector)
    {
        towardLight = towardLightVector;
        towardLight.normalize();
    }

    Ray DirectionalLight::getRayToLight(const math::Point3D &point) const
    {
        return Ray(point, towardLight);
    }

    double DirectionalLight::getDistanceToLight(const math::Point3D &) const
    {
        return 1000.0;
    }

    math::Point3D DirectionalLight::getPosition() const
    {
        return math::Point3D(0, 0, 0);
    }

    math::Vector3D DirectionalLight::vectorSurfaceToLight(const math::Point3D &) const
    {
        return towardLight;
    }

}
