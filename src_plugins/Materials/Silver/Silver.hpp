/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** Silver material plugin
*/

#ifndef RAYTRACER_SILVER_HPP
#define RAYTRACER_SILVER_HPP

#include <string>
#include "Core/Materials/AReflectiveMaterial.hpp"

namespace RayTracer {

    class Silver : public AReflectiveMaterial {
        public:
            explicit Silver(const math::Vector3D &albedo = {0.92, 0.92, 0.96}) : _albedo(albedo) {}

            ~Silver() override = default;

            math::Vector3D getAlbedo(const math::Point3D & /*point*/, const math::Vector3D & /*normal*/) const override { return _albedo; }

            ScatterResult scatter(const Ray &in, const math::Point3D &point, const math::Vector3D &normal) const override
            {
                math::Vector3D reflected = reflect(in._direction, normal);
                return ScatterResult{_albedo, Ray(point, reflected), 0.55};
            }

            std::string getTypeName() const override { return "silver"; }

        private:
            math::Vector3D _albedo;
    };

}

#endif /* RAYTRACER_SILVER_HPP */
