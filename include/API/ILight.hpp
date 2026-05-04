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

    class ILight {
    public:
        virtual ~ILight() = default;

        /**
         * @brief Get the ray from the light source to a target point.
         * Useful for shadow calculations.
         */
        virtual Ray getRayToLight(const math::Point3D &point) const = 0;

        /**
         * @brief Get the distance from a point to the light source.
         */
        virtual double getDistanceToLight(const math::Point3D &point) const = 0;

        /**
         * @brief Get the position of the light (if applicable).
         */
        virtual math::Point3D getPosition() const = 0;

        virtual math::Vector3D vectorSurfaceToLight(const math::Point3D &surface) const = 0;

        virtual std::string getTypeName() const = 0;
    };

}

#endif /* RAYTRACER_ILIGHT_HPP */
