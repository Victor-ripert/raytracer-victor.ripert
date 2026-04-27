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
    #include "IObject.hpp"
    #include "Ray.hpp"
    #include "Color.hpp"

namespace RayTracer {
    class Sphere : public IObject {
        private:
        public:
            math::Point3D _pos;
            double _radius;
            Color color;
            math::Point3D _last_hit_point;

            Sphere();
            Sphere(math::Point3D pos, double radius, Color color);
            bool hits(Ray ray_obj) override; // analytic
            bool hits_geometric(Ray ray_obj); // geometric
            math::Point3D getHitPoint(Ray ray_obj, double hit_distance);
            void display();
            math::Point3D get_center() override;
            Color get_color() override;
            math::Point3D get_last_hit_point() override;
            math::Vector3D getNormalFromPointOnSphere(math::Point3D point) override;
    };

    bool solveQuadratic(const double &a, const double &b, const double &c, double &x0, double &x1);
}

#endif /* SPHERE_HPP */