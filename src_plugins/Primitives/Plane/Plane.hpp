/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Plane Plugin
*/

#ifndef RAYTRACER_PLUGINS_PLANE_HPP
#define RAYTRACER_PLUGINS_PLANE_HPP

#include <cmath>
#include <iostream>
#include <memory>
#include <string>

#include "API/APrimitive.hpp"
#include "Math/Ray.hpp"
#include "Core/Render/Color.hpp"

namespace RayTracer {

    class ITransformation;

    class Plane : public APrimitive {
        private:
            std::shared_ptr<ITransformation> _transform{};
            math::Point3D _point;
            math::Vector3D _normal;
            Color _color;

        public:
            Plane();
            Plane(const math::Point3D &point, const math::Vector3D &normal, const Color &col);

            bool hits(const Ray &ray, double tMin, double tMax, HitRecord &record) const override;
            void applyConfig(const libconfig::Setting &node) override;
            std::shared_ptr<ITransformation> getTransform() const override;
            void setTransform(std::shared_ptr<ITransformation> transform) override;
            std::string getTypeName() const override;
    };

}

#endif /* RAYTRACER_PLUGINS_PLANE_HPP */
