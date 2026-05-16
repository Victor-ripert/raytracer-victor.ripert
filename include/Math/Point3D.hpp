/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Raytracing_bootstrap
*/

#ifndef POINT3D_HPP
    #define POINT3D_HPP
    #include <cmath>
    #include <iostream>

namespace math {
    class Vector3D;
}

namespace math {
    /**
     * @brief Class representing a 3D point in space.
     */
    class Point3D {
        private:
        public:
            double _x, _y, _z;

            /** @brief Default constructor (0,0,0). */
            Point3D();
            /** @brief Constructor with coordinates. */
            Point3D(double x, double y, double z);
            /** @brief Print point coordinates to stdout. */
            void display();
            /** @brief Calculate Euclidean distance to another point. */
            double distance_point(const Point3D point) const;

            Point3D operator+(const Vector3D vec) const;
            void operator+=(const Vector3D vec);
            Point3D operator-(const Vector3D vec) const;
            void operator-=(const Vector3D vec);

            Point3D operator+(const Point3D point) const;
            void operator+=(const Point3D point);
            Vector3D operator-(const Point3D point) const;
            void operator-=(const Point3D point);

            bool operator==(const Point3D point) const;
    };
}

#endif /* POINT3D_HPP */