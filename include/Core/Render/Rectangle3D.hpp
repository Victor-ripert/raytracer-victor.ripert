/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Raytracing_bootstrap
*/

#ifndef RECTANGLE_HPP
    #define RECTANGLE_HPP
    #include <cmath>
    #include <iostream>
    #include "Math/Ray.hpp"

namespace RayTracer {
    class Rectangle3D {
        private:
        public:
            math::Point3D origin;
            math::Vector3D bottom_side;
            math::Vector3D left_side;

            Rectangle3D();
            math::Point3D pointAt(double u, double v);
            void display();
    };
}

#endif /* RECTANGLE_HPP */