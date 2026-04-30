/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Plane / infinite plane primitive (mandatory in the subject)
*/

#ifndef PLANE_HPP
#define PLANE_HPP

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include "IObject.hpp"
#include "../Ray.hpp"
#include "../Color.hpp"

namespace RayTracer {

    class IMaterial;
    class ITransformation;

    class Plane : public IObject {
        private:
            std::shared_ptr<IMaterial> _material{};
            std::shared_ptr<ITransformation> _transform{};
            mutable math::Point3D _last_hit_point{};
            mutable math::Vector3D _last_hit_normal{};

        public:
            math::Point3D _point;
            math::Vector3D _normal;
            Color color;

            Plane();
            Plane(const math::Point3D &point, const math::Vector3D &normal, const Color &color);
            void display();

            bool hits(const Ray &ray, double tMin, double tMax) const override;
            math::Point3D get_last_hit_point() const override;
            math::Vector3D get_last_hit_normal() const override;
            Color get_last_hit_surface_color() const override;
            std::shared_ptr<IMaterial> getMaterial() const override;
            void setMaterial(std::shared_ptr<IMaterial> material) override;
            std::shared_ptr<ITransformation> getTransform() const override;
            void setTransform(std::shared_ptr<ITransformation> transform) override;
            std::string getTypeName() const override;
    };

}

#endif /* PLANE_HPP */
