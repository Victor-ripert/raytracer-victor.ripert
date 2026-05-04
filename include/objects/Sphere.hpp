/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Sphere Plugin
*/

#ifndef RAYTRACER_OBJECTS_SPHERE_HPP
#define RAYTRACER_OBJECTS_SPHERE_HPP

#include <cmath>
#include <iostream>
#include <memory>
#include <string>

#include "API/IPrimitive.hpp"
#include "Math/Ray.hpp"
#include "Core/Render/Color.hpp"

namespace RayTracer {

    class IMaterial;
    class ITransformation;

    class Sphere : public IPrimitive {
        private:
            std::shared_ptr<IMaterial> _material{};
            std::shared_ptr<ITransformation> _transform{};
            mutable math::Point3D _last_hit_point{};
            mutable math::Vector3D _last_hit_normal{};

        public:
            math::Point3D _pos;
            double _radius;
            Color color;

            Sphere();
            Sphere(math::Point3D pos, double radius, Color color);

            bool hits(const Ray &ray, double tMin, double tMax) const override;
            void applyConfig(const PrimitiveConfig &config) override;
            math::Point3D get_last_hit_point() const override;
            math::Vector3D get_last_hit_normal() const override;
            Color get_last_hit_surface_color() const override;
            std::shared_ptr<IMaterial> getMaterial() const override;
            void setMaterial(std::shared_ptr<IMaterial> material) override;
            std::shared_ptr<ITransformation> getTransform() const override;
            void setTransform(std::shared_ptr<ITransformation> transform) override;
            std::string getTypeName() const override;
    };

    bool solveQuadratic(const double &a, const double &b, const double &c, double &x0, double &x1);

}

#endif /* RAYTRACER_OBJECTS_SPHERE_HPP */
