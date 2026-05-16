/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** AReflectiveMaterial.hpp
*/

#ifndef RAYTRACER_AREFLECTIVEMATERIAL_HPP
#define RAYTRACER_AREFLECTIVEMATERIAL_HPP

#include "API/IMaterial.hpp"

namespace RayTracer {

    class AReflectiveMaterial : public IMaterial {
        public:
            void applyConfig(const libconfig::Setting & /*node*/) override {}

        protected:
            static math::Vector3D reflect(const math::Vector3D &direction, math::Vector3D normal)
            {
                normal.normalize();
                return direction - normal * (2.0 * direction.dot(normal));
            }
    };

}

#endif /* RAYTRACER_AREFLECTIVEMATERIAL_HPP */
