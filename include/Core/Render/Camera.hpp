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
#include "Math/Vector3D.hpp"
#include "Core/Render/Rectangle3D.hpp"

namespace RayTracer {
    class Camera {
        public:
            math::Point3D origin;
            Rectangle3D screen;

            Camera();
            void setImageDimensions(unsigned int width, unsigned int height);
            void setVerticalFovDegrees(double degrees);
            void setRotationDegrees(const math::Vector3D &eulerDegrees);
            void rebuildViewPlane();

            Ray ray(double u, double v);
            unsigned int _imageWidth = 0;
            unsigned int _imageHeight = 0;
            double _verticalFovDegrees = 72.0;
            math::Vector3D _rotationDegrees{0, 0, 0};
    };
}

#endif /* CAMERA_HPP */
