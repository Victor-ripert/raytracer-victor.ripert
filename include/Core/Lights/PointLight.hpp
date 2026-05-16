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
    /**
     * @brief A light source that radiates in all directions from a specific point.
     */
    class PointLight : public ILight {
        public:
            math::Point3D origin; /**< The 3D position of the light source */

            /** @brief Default constructor (at origin). */
            PointLight();
            /** @brief Constructor with custom position. */
            PointLight(math::Point3D point);
            
            /** @return Ray from hit point towards the light origin. */
            Ray getRayToLight(const math::Point3D &point) const override;
            /** @return Distance between hit point and light origin. */
            double getDistanceToLight(const math::Point3D &point) const override;
            /** @return The light's origin. */
            math::Point3D getPosition() const override;
            /** @return Normalized vector from surface point to light origin. */
            math::Vector3D vectorSurfaceToLight(const math::Point3D &surface) const override;
            /** @return "point" */
            std::string getTypeName() const override { return "point"; }
    };
}

#endif /* POINTLIGHT_HPP */
