/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** DirectionalLight
*/

#ifndef RAYTRACER_DIRECTIONALLIGHT_HPP
#define RAYTRACER_DIRECTIONALLIGHT_HPP

#include "API/ILight.hpp"

namespace RayTracer {

    class DirectionalLight : public ILight {
        public:
            math::Point3D _origin;
            math::Vector3D _direction; // Is it the direction of the light ??
            double _lightning_angle; // Angle of the opening of the light (the mor open it is, the more area is lighted)

            DirectionalLight();
            DirectionalLight(math::Point3D origin, math::Vector3D direction, double lightning_angle);

            Ray getRayToLight(const math::Point3D &point) const override;
            double getDistanceToLight(const math::Point3D &point) const override;
            math::Point3D getPosition() const override;
            math::Vector3D vectorSurfaceToLight(const math::Point3D &surface) const override;
            std::string getTypeName() const override { return "directional"; }
            bool isInLigthningWidth(const math::Vector3D ray_to_light_vector) const override;
    };

}

#endif /* RAYTRACER_DIRECTIONALLIGHT_HPP */
