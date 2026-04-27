/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Raytracing_bootstrap
*/

#ifndef PLAIN_HPP
    #define PLAIN_HPP
    #include <cmath>
    #include <iostream>
    #include "Ray.hpp"

namespace RayTracer {
    class Plain {
        private:
        public:
            math::Point3D center;
            math::Vector3D orientation;

            Plain();
            Plain(math::Point3D pos, math::Vector3D ori);
            bool hits(Ray ray_obj);
            void display();
    };

    bool intersectPlane(math::Vector3D &n, const math::Vector3D &p0, const math::Vector3D &l0, const math::Vector3D &l);
}

#endif /* PLAIN_HPP */