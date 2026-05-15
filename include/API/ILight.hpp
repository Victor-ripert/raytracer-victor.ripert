/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** ILight.hpp
*/

#ifndef RAYTRACER_ILIGHT_HPP
#define RAYTRACER_ILIGHT_HPP

#include <string>
#include "../Math/Point3D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Math/Ray.hpp"

namespace RayTracer {

    /**
     * @brief Interface for light sources in the scene.
     */
    class ILight {
    public:
        virtual ~ILight() = default;

        /**
         * @brief Get the ray from a surface point towards the light source.
         * @param point The surface point being shaded.
         * @return Ray pointing towards the light.
         */
        virtual Ray getRayToLight(const math::Point3D &point) const = 0;

        /**
         * @brief Get the distance from a surface point to the light source.
         * @param point The surface point.
         * @return Distance to the light.
         */
        virtual double getDistanceToLight(const math::Point3D &point) const = 0;

        /**
         * @brief Get the position of the light source.
         * @return The 3D position.
         */
        virtual math::Point3D getPosition() const = 0;

        /**
         * @brief Get the normalized direction vector from a point to the light.
         * @param surface The point on the surface.
         * @return Normalized direction vector.
         */
        virtual math::Vector3D vectorSurfaceToLight(const math::Point3D &surface) const = 0;

        /** @return The type of the light (e.g., "point", "directional"). */
        virtual std::string getTypeName() const = 0;
    };

}

#endif /* RAYTRACER_ILIGHT_HPP */
