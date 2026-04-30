/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Raytracing_bootstrap
*/

#ifndef SPHERE_HPP
#define SPHERE_HPP
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

    class Sphere : public IObject {
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
            bool hits_geometric(Ray ray_obj); // geometric
            math::Point3D getHitPoint(Ray ray_obj, double hit_distance);
            void display();
            math::Point3D get_center();
            Color get_color();
            math::Vector3D getNormalFromPointOnSphere(math::Point3D point);

            bool hits(const Ray &ray, double tMin, double tMax) const override;
            math::Point3D get_last_hit_point() const override;
            math::Vector3D get_last_hit_normal() const override;
            Color get_last_hit_surface_color() const override;
            std::shared_ptr<IMaterial> getMaterial() const override;
            void setMaterial(std::shared_ptr<IMaterial> material) override;
            std::shared_ptr<ITransformation> getTransform() const override;
            void setTransform(
                std::shared_ptr<ITransformation> transform) override;
            std::string getTypeName() const override;
    };

    bool solveQuadratic(const double &a, const double &b, const double &c, double &x0, double &x1);
}

#endif /* SPHERE_HPP */
