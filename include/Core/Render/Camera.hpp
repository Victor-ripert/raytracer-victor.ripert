/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Raytracing_bootstrap
*/

#ifndef CAMERA_HPP
    #define CAMERA_HPP
    #include <cmath>
    #include <iostream>
    #include "Math/Ray.hpp"
    #include "Core/Render/Rectangle3D.hpp"

namespace RayTracer {
    class Camera {
        private:
        public:
            math::Point3D origin;
            Rectangle3D screen;
            // double _rotation;
            // double _resolution;
            // double _fov;

            Camera();
            Ray ray(double u, double v);
            void display();
    };
}

#endif /* CAMERA_HPP */