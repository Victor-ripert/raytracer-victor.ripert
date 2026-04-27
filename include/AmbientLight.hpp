/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Raytracing_bootstrap
*/

#ifndef AMBIANTLIGHT_HPP
    #define AMBIANTLIGHT_HPP
    #include <cmath>
    #include <iostream>
    #include "Ray.hpp"
    #include "Rectangle3D.hpp"

namespace RayTracer {
    class AmbiantLight {
        private:
        public:
            math::Point3D origin;

            AmbiantLight();
            AmbiantLight(math::Point3D point);
            Ray ray(math::Point3D point);
            void display();
    };
}

#endif /* AMBIANTLIGHT_HPP */