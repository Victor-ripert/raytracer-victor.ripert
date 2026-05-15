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
    /**
     * @brief Class representing a rectangle in 3D space, used for the camera screen.
     */
    class Rectangle3D {
        private:
        public:
            math::Point3D origin;      /**< Top-left corner of the rectangle */
            math::Vector3D bottom_side; /**< Vector representing the bottom edge */
            math::Vector3D left_side;   /**< Vector representing the left edge */

            Rectangle3D();
            /** 
             * @brief Calculate a point on the rectangle based on normalized coordinates.
             * @param u Horizontal interpolation [0, 1].
             * @param v Vertical interpolation [0, 1].
             * @return The 3D point.
             */
            math::Point3D pointAt(double u, double v);
            /** @brief Display rectangle properties to stdout. */
            void display();
    };
}

#endif /* RECTANGLE_HPP */