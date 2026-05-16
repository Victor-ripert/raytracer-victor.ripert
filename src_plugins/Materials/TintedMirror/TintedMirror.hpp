/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** TintedMirror material plugin
*/

#ifndef RAYTRACER_TINTEDMIRROR_HPP
#define RAYTRACER_TINTEDMIRROR_HPP

#include <string>
#include "Core/Materials/AReflectiveMaterial.hpp"

namespace RayTracer {

    class TintedMirror : public AReflectiveMaterial {
        public:
            explicit TintedMirror(const math::Vector3D &albedo = {0.40, 0.42, 0.48}) : _albedo(albedo) {}

            ~TintedMirror() override = default;

            math::Vector3D getAlbedo(const math::Point3D & /*point*/, const math::Vector3D & /*normal*/) const override { return _albedo; }

            ScatterResult scatter(const Ray &in, const math::Point3D &point, const math::Vector3D &normal) const override
            {
                math::Vector3D reflected = reflect(in._direction, normal);
                return ScatterResult{_albedo, Ray(point, reflected), 1.0};
            }

            std::string getTypeName() const override { return "tinted_mirror"; }

        private:
            math::Vector3D _albedo;
    };

}

#endif /* RAYTRACER_TINTEDMIRROR_HPP */
