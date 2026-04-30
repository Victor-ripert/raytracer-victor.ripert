/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** ITransformation.hpp
*/

#ifndef RAYTRACER_ITRANSFORMATION_HPP
#define RAYTRACER_ITRANSFORMATION_HPP

#include <string>
#include "../Math/Point3D.hpp"
#include "../Math/Ray.hpp"
#include "../Math/Vector3D.hpp"

namespace RayTracer {

    class ITransformation {
    public:
        virtual ~ITransformation() = default;

        virtual Ray applyInverse(const Ray &ray) const = 0;
        virtual math::Point3D transform_point_forward(const math::Point3D &object_space_point) const = 0;
        virtual math::Vector3D transform_normal_forward(const math::Vector3D &object_space_normal) const = 0;

        virtual std::string getTypeName() const = 0;
    };

}

#endif /* RAYTRACER_ITRANSFORMATION_HPP */
