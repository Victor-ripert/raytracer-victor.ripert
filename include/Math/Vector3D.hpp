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
    class Vector3D {
        private:
        public:
            double _x, _y, _z;

            Vector3D();
            Vector3D(double x, double y, double z);
            Vector3D(Point3D point);
            void display();
            double length();
            double dot(const Vector3D &vec) const;
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