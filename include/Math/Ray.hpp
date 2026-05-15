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
    /**
     * @brief Class representing a semi-infinite line (Ray) in 3D space.
     * 
     * Defined by an origin point and a direction vector.
     */
    class Ray {
        private:
        public:
            math::Point3D _origin;    /**< Starting point of the ray */
            math::Vector3D _direction; /**< Direction vector of the ray */

            /** @brief Default constructor. */
            Ray();
            /** @brief Constructor with origin and direction. */
            Ray(math::Point3D origin, math::Vector3D direction);
            /** @brief Print ray properties to stdout. */
            void display();
    };
}

#endif /* RAY_HPP */