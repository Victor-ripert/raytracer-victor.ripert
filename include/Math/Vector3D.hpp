/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Raytracing_bootstrap
*/

#ifndef VECTOR3D_HPP
    #define VECTOR3D_HPP
    #include <cmath>
    #include <iostream>

namespace math {
    class Point3D;
}

namespace math {
    /**
     * @brief Class representing a 3D vector and its mathematical operations.
     */
    class Vector3D {
        private:
        public:
            double _x, _y, _z;

            /** @brief Default constructor (0,0,0). */
            Vector3D();
            /** @brief Constructor with coordinates. */
            Vector3D(double x, double y, double z);
            /** @brief Conversion constructor from Point3D. */
            Vector3D(Point3D point);
            
            /** @brief Print vector coordinates to stdout. */
            void display();
            /** @return The Euclidean length of the vector. */
            double length();
            /** @brief Calculate the dot product with another vector. */
            double dot(const Vector3D &vec) const;
            /** @return A new normalized (unit length) vector. */
            Vector3D normalize();

            Vector3D operator+(const Vector3D vec) const;
            void operator+=(const Vector3D vec);

            Vector3D operator-(const Vector3D vec) const;
            void operator-=(const Vector3D vec);

            Vector3D operator*(const Vector3D vec) const;
            Vector3D operator*(double nb) const;
            void operator*=(const Vector3D vec);
            void operator*=(double nb);

            Vector3D operator/(const Vector3D vec) const;
            Vector3D operator/(double nb) const;
            void operator/=(const Vector3D vec);
            void operator/=(double nb);
    };
}

#endif /* VECTOR3D_HPP */