/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Sphere Plugin
*/

#ifndef RAYTRACER_PLUGINS_SPHERE_HPP
#define RAYTRACER_PLUGINS_SPHERE_HPP

#include <cmath>
#include <iostream>
#include <memory>
#include <string>

#include "API/APrimitive.hpp"
#include "Math/Ray.hpp"
#include "Core/Render/Color.hpp"

namespace RayTracer {

    class ITransformation;

    class Sphere : public APrimitive {
        private:
            std::shared_ptr<ITransformation> _transform{};
            math::Point3D _pos;
            double _radius;
            Color _color;

        public:
            Sphere();
            Sphere(math::Point3D pos, double radius, Color color);

            bool hits(const Ray &ray, double tMin, double tMax, HitRecord &record) const override;
            void applyConfig(const libconfig::Setting &node) override;
            std::shared_ptr<ITransformation> getTransform() const override;
            void setTransform(std::shared_ptr<ITransformation> transform) override;
            std::string getTypeName() const override;
    };

    bool solveQuadratic(const double &a, const double &b, const double &c, double &x0, double &x1);

}

#endif /* RAYTRACER_PLUGINS_SPHERE_HPP */
