/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** DirectionalLight
*/

#include "Core/Lights/DirectionalLight.hpp"

namespace RayTracer {

    DirectionalLight::DirectionalLight() {
        _direction = math::Vector3D(0, 0, -1);
        _origin = math::Point3D(0, 0, 0);
        _lightning_angle = 45.0;
    }


    DirectionalLight::DirectionalLight(math::Point3D origin, math::Vector3D direction, double lightning_angle)
    {
        std::cerr << "direction: " << direction._x << direction._y << direction._z << std::endl;
        std::cerr << "origin: " << origin._x << origin._y << origin._z << std::endl;
        std::cerr << "angle: " << lightning_angle << std::endl;
        _direction = direction;
        _direction.normalize();
        _lightning_angle = lightning_angle;
        _origin = origin;
    }

    Ray DirectionalLight::getRayToLight(const math::Point3D &point) const
    {
        math::Vector3D direction = _origin - point;
        return Ray(point, direction);
    }

    double DirectionalLight::getDistanceToLight(const math::Point3D &point) const
    {
        return _origin.distance_point(point);
    }

    math::Point3D DirectionalLight::getPosition() const
    {
        return _origin;
    }

    math::Vector3D DirectionalLight::vectorSurfaceToLight(const math::Point3D &surface) const
    {
        math::Vector3D toward(_origin - surface);
        toward.normalize();
        return toward;
    }

    bool DirectionalLight::isInLigthningWidth(const math::Vector3D ray_to_light_vector) const {
        math::Vector3D opposite = ray_to_light_vector * -1.0; // Negation du vector parce qu'il fait objet->lumière et pas lumier->obj (et du coup tous les angles sont égaux a 180°)
        if (_direction.angle(opposite) > _lightning_angle) {
            return false;
        }
        return true;
    }

}
