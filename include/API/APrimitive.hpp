/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** APrimitive.hpp
*/

#ifndef RAYTRACER_APRIMITIVE_HPP
#define RAYTRACER_APRIMITIVE_HPP

#include <memory>

#include "IMaterial.hpp"
#include "IPrimitive.hpp"

namespace RayTracer {

    class APrimitive : public IPrimitive {
        protected:
            std::shared_ptr<IMaterial> _material{};

        public:
            ~APrimitive() override = default;

            std::shared_ptr<IMaterial> getMaterial() const override { return _material; }

            void setMaterial(std::shared_ptr<IMaterial> material) override { _material = std::move(material); }
        };

}

#endif /* RAYTRACER_APRIMITIVE_HPP */
