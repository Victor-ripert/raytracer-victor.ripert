/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** IMaterial.hpp
*/

#ifndef RAYTRACER_IMATERIAL_HPP
#define RAYTRACER_IMATERIAL_HPP

#include <libconfig.h++>
#include <optional>
#include <string>
#include "../Math/Point3D.hpp"
#include "../Math/Ray.hpp"
#include "../Math/Vector3D.hpp"

namespace RayTracer {

    struct ScatterResult {
        math::Vector3D attenuation{1, 1, 1};
        std::optional<Ray> scattered;
        double blend = 1.0;
    };

    class IMaterial {
    public:
        virtual ~IMaterial() = default;

        virtual void applyConfig(const libconfig::Setting &node) = 0;

        virtual math::Vector3D getAlbedo(const math::Point3D &point, const math::Vector3D &normal) const = 0;

        virtual ScatterResult scatter(const Ray &in, const math::Point3D &point, const math::Vector3D &normal) const = 0;

        virtual std::string getTypeName() const = 0;
    };

}

#endif /* RAYTRACER_IMATERIAL_HPP */
