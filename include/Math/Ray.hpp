/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Raytracing_bootstrap
*/

#ifndef RAY_HPP
    #define RAY_HPP
    #include <cmath>
    #include <iostream>
    #include "Vector3D.hpp"
#include "Point3D.hpp"

namespace RayTracer {
    class Ray {
        private:
        public:
            math::Point3D _origin;
            math::Vector3D _direction;

            Ray();
            Ray(math::Point3D origin, math::Vector3D direction);
            void display();
    };
}

#endif /* RAY_HPP */