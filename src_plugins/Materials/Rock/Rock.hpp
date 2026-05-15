/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** Rock material plugin
*/

#ifndef RAYTRACER_ROCK_HPP
#define RAYTRACER_ROCK_HPP

#include <string>
#include "API/IMaterial.hpp"

namespace RayTracer {

    class Rock : public IMaterial {
        public:
            explicit Rock(const math::Vector3D &albedo = {0.35, 0.30, 0.25}) : _albedo(albedo) {}

            ~Rock() override = default;

            void applyConfig(const libconfig::Setting & /*node*/) override {}

            math::Vector3D getAlbedo(const math::Point3D & /*point*/, const math::Vector3D & /*normal*/) const override { return _albedo; }

            ScatterResult scatter(const Ray & /*in*/, const math::Point3D & /*point*/, const math::Vector3D & /*normal*/) const override
            {
                return ScatterResult{_albedo, std::nullopt};
            }

            std::string getTypeName() const override { return "rock"; }

        private:
            math::Vector3D _albedo;
    };

}

#endif /* RAYTRACER_ROCK_HPP */
