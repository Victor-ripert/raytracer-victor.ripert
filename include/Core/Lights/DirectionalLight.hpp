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

    /**
     * @brief Light source that illuminates from a constant direction (e.g., the Sun).
     */
    class DirectionalLight : public ILight {
        public:
            math::Vector3D towardLight{0, 1, 0}; /**< Unit vector pointing towards the light source */

            /** @brief Default constructor (pointing up). */
            DirectionalLight();
            /** @brief Constructor with a custom direction. */
            explicit DirectionalLight(math::Vector3D unitTowardLight);

            /** @return Ray from hit point towards infinity in the light direction. */
            Ray getRayToLight(const math::Point3D &point) const override;
            /** @return Infinity, as directional lights have no position. */
            double getDistanceToLight(const math::Point3D &point) const override;
            /** @return A point at infinity. */
            math::Point3D getPosition() const override;
            /** @return The constant towardLight vector. */
            math::Vector3D vectorSurfaceToLight(const math::Point3D &surface) const override;
            /** @return "directional" */
            std::string getTypeName() const override { return "directional"; }
    };

}

#endif /* RAYTRACER_DIRECTIONALLIGHT_HPP */
