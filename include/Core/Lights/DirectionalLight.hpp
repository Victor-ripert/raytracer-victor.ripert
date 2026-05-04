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
            math::Vector3D towardLight{0, 1, 0};

            DirectionalLight();
            explicit DirectionalLight(math::Vector3D unitTowardLight);

            Ray getRayToLight(const math::Point3D &point) const override;
            double getDistanceToLight(const math::Point3D &point) const override;
            math::Point3D getPosition() const override;
            math::Vector3D vectorSurfaceToLight(const math::Point3D &surface) const override;
            std::string getTypeName() const override { return "directional"; }
    };

}

#endif /* RAYTRACER_DIRECTIONALLIGHT_HPP */
