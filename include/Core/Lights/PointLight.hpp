/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** PointLight
*/

#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "API/ILight.hpp"

namespace RayTracer {
    class PointLight : public ILight {
        public:
            math::Point3D origin;

            PointLight();
            PointLight(math::Point3D point);

            Ray getRayToLight(const math::Point3D &point) const override;
            double getDistanceToLight(const math::Point3D &point) const override;
            math::Point3D getPosition() const override;
            math::Vector3D vectorSurfaceToLight(const math::Point3D &surface) const override;
            std::string getTypeName() const override { return "point"; }
            bool isInLigthningWidth(const math::Vector3D ray_to_light_vector) const override;
    };
}

#endif /* POINTLIGHT_HPP */
