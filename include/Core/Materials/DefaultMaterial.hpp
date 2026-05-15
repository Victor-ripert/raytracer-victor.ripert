/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** DefaultMaterial.hpp
*/

#ifndef RAYTRACER_DEFAULTMATERIAL_HPP
#define RAYTRACER_DEFAULTMATERIAL_HPP

#include <string>
#include "API/IMaterial.hpp"
#include "Core/Render/Color.hpp"

namespace RayTracer {

    /**
     * @brief A simple matte material that just reflects a constant color (albedo).
     */
    class DefaultMaterial : public IMaterial {
    public:
        /**
         * @brief Construct a new Default Material.
         * @param color The RGB color of the material.
         */
        explicit DefaultMaterial(const Color &color)
            : _albedo(
                static_cast<double>(color.r) / 255.0,
                static_cast<double>(color.g) / 255.0,
                static_cast<double>(color.b) / 255.0) {}

        ~DefaultMaterial() override = default;

        /** @return The constant albedo vector. */
        math::Vector3D getAlbedo(const math::Point3D & /*point*/, const math::Vector3D & /*normal*/) const override { return _albedo; }

        /** @return ScatterResult with attenuation but no scattered ray (matte). */
        ScatterResult scatter(const Ray & /*in*/, const math::Point3D & /*point*/, const math::Vector3D & /*normal*/) const override {return ScatterResult{_albedo, std::nullopt};}

        /** @return "default" */
        std::string getTypeName() const override { return "default"; }

    private:
        math::Vector3D _albedo; /**< Internal RGB albedo normalized to [0, 1] */
    };

}

#endif /* RAYTRACER_DEFAULTMATERIAL_HPP */
