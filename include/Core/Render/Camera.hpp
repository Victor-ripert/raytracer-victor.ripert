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
#include <libconfig.h++>

namespace RayTracer {
    /**
     * @brief The Camera class represents the observer's viewpoint.
     * 
     * It handles the view plane projection, FOV, and generates rays for 
     * each pixel of the image.
     */
    class Camera {
        public:
            math::Point3D origin;      /**< World position of the camera */
            Rectangle3D screen;        /**< Virtual screen (view plane) in the scene */

            Camera();

            /** @brief Apply configuration from a libconfig node. */
            void applyConfig(const libconfig::Setting &node);

            /** @brief Set final image resolution. */
            void setImageDimensions(unsigned int width, unsigned int height);

            /** @brief Set the vertical Field of View. */
            void setVerticalFovDegrees(double degrees);

            /** @brief Set camera orientation using Euler angles. */
            void setRotationDegrees(const math::Vector3D &eulerDegrees);

            /** @brief Recompute the view plane based on FOV and rotation. */
            void rebuildViewPlane();

            /** 
             * @brief Generate a ray for a normalized pixel coordinate.
             * @param u Horizontal coordinate [0, 1].
             * @param v Vertical coordinate [0, 1].
             * @return A Ray starting from origin passing through the screen.
             */
            Ray ray(double u, double v);

            unsigned int _imageWidth = 0;
            unsigned int _imageHeight = 0;
            double _verticalFovDegrees = 72.0;
            math::Vector3D _rotationDegrees{0, 0, 0};
    };
}

#endif /* CAMERA_HPP */
