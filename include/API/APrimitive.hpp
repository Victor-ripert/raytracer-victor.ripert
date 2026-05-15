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

    /**
     * @brief Abstract base class for primitives, providing common material management.
     */
    class APrimitive : public IPrimitive {
        protected:
            std::shared_ptr<IMaterial> _material{}; /**< The material applied to the primitive */

        public:
            virtual ~APrimitive() override = default;

            /** @return The material associated with this primitive. */
            std::shared_ptr<IMaterial> getMaterial() const override { return _material; }

            /** @param material The new material to assign to this primitive. */
            void setMaterial(std::shared_ptr<IMaterial> material) override { _material = std::move(material); }
        };

}

#endif /* RAYTRACER_APRIMITIVE_HPP */
