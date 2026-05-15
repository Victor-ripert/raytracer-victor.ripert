/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** Default.hpp
*/

#ifndef RAYTRACER_DEFAULT_HPP
#define RAYTRACER_DEFAULT_HPP

#include <string>
#include "API/IMaterial.hpp"
#include "Core/Render/Color.hpp"

namespace RayTracer {

    class Default : public IMaterial {
        public:
            explicit Default(const Color &color)
                : _albedo(
                    static_cast<double>(color.r) / 255.0,
                    static_cast<double>(color.g) / 255.0,
                    static_cast<double>(color.b) / 255.0) {}

            ~Default() override = default;

            void applyConfig(const libconfig::Setting & /*node*/) override {}

            math::Vector3D getAlbedo(const math::Point3D & /*point*/, const math::Vector3D & /*normal*/) const override { return _albedo; }

            ScatterResult scatter(const Ray & /*in*/, const math::Point3D & /*point*/, const math::Vector3D & /*normal*/) const override {return ScatterResult{_albedo, std::nullopt};}

            std::string getTypeName() const override { return "default"; }

        private:
            math::Vector3D _albedo;
    };

}

#endif /* RAYTRACER_DEFAULT_HPP */
