/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** IMaterial.hpp
*/

#ifndef RAYTRACER_IMATERIAL_HPP
#define RAYTRACER_IMATERIAL_HPP

#include <optional>
#include <string>
#include "../Math/Point3D.hpp"
#include "../Math/Ray.hpp"
#include "../Math/Vector3D.hpp"

namespace RayTracer {

    /**
     * @brief Result of a ray scattering on a surface.
     */
    struct ScatterResult {
        math::Vector3D attenuation{1, 1, 1}; /**< How much light is absorbed/reflected by the material */
        std::optional<Ray> scattered;         /**< The new ray after reflection/refraction (if any) */
    };

    /**
     * @brief Interface for materials defining surface properties.
     */
    class IMaterial {
    public:
        virtual ~IMaterial() = default;

        /**
         * @brief Get the base color (albedo) of the material at a specific point.
         * @param point The hit point on the surface.
         * @param normal The surface normal at the hit point.
         * @return Color as a Vector3D (RGB normalized to [0, 1]).
         */
        virtual math::Vector3D getAlbedo(const math::Point3D &point, const math::Vector3D &normal) const = 0;

        /**
         * @brief Determine how a ray scatters when hitting a surface with this material.
         * @param in The incoming ray.
         * @param point The hit point on the surface.
         * @param normal The surface normal at the hit point.
         * @return A ScatterResult containing attenuation and the scattered ray.
         */
        virtual ScatterResult scatter(const Ray &in, const math::Point3D &point, const math::Vector3D &normal) const = 0;

        /** @return The string type name of the material (e.g., "lambertian"). */
        virtual std::string getTypeName() const = 0;
    };

}

#endif /* RAYTRACER_IMATERIAL_HPP */
