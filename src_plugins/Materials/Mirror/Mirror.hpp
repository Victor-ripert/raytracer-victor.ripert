/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** Mirror material plugin
*/

#ifndef RAYTRACER_MIRROR_HPP
#define RAYTRACER_MIRROR_HPP

#include <string>
#include "Core/Materials/AReflectiveMaterial.hpp"

namespace RayTracer {

    class Mirror : public AReflectiveMaterial {
        public:
            explicit Mirror(const math::Vector3D &albedo = {1.0, 1.0, 1.0}) : _albedo(albedo) {}

            ~Mirror() override = default;

            math::Vector3D getAlbedo(const math::Point3D & /*point*/, const math::Vector3D & /*normal*/) const override { return _albedo; }

            ScatterResult scatter(const Ray &in, const math::Point3D &point, const math::Vector3D &normal) const override
            {
                math::Vector3D reflected = reflect(in._direction, normal);
                return ScatterResult{_albedo, Ray(point, reflected), 1.0};
            }

            std::string getTypeName() const override { return "mirror"; }

        private:
            math::Vector3D _albedo;
    };

}

#endif /* RAYTRACER_MIRROR_HPP */
