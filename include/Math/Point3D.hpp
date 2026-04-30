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
    class Point3D {
        private:
        public:
            double _x, _y, _z;

            Point3D();
            Point3D(double x, double y, double z);
            void display();
            double distance_point(const Point3D point) const;

            Point3D operator+(const Vector3D vec) const;
            void operator+=(const Vector3D vec);
            Point3D operator-(const Vector3D vec) const;
            void operator-=(const Vector3D vec);

            Point3D operator+(const Point3D point) const;
            void operator+=(const Point3D point);
            Point3D operator-(const Point3D point) const;
            void operator-=(const Point3D point);

            bool operator==(const Point3D point) const;
    };
}

#endif /* POINT3D_HPP */