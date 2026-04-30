/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Raytracing_bootstrap
*/

#ifndef AMBIENTLIGHT_HPP
#define AMBIENTLIGHT_HPP
#include <cmath>
#include <iostream>
#include "Ray.hpp"
#include "Rectangle3D.hpp"

namespace RayTracer {
    class AmbientLight {
        private:
        public:
            math::Point3D origin;

            AmbientLight();
            AmbientLight(math::Point3D point);
            Ray ray(math::Point3D point);
            void display();
    };
}

#endif /* AMBIENTLIGHT_HPP */
