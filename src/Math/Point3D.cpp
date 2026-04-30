/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Raytracing_bootstrap
*/

#include "../../include/Math/Point3D.hpp"
#include "../../include/Math/Vector3D.hpp"

namespace math {
    Point3D::Point3D() {
        _x = 0;
        _y = 0;
        _z = 0;
    }

    Point3D::Point3D(double x, double y, double z) : _x(x), _y(y), _z(z) {}

    void Point3D::display() {
        std::cout << "Vector(" << _x << ", " << _y << ", " << _z << ")" << std::endl;
    }

    double Point3D::distance_point(const Point3D point) const {
        double result = std::sqrt(((_x - point._x) * (_x - point._x)) +
            ((_y - point._y) * (_y - point._y)) +
            ((_z - point._z) * (_z - point._z)));
        return std::sqrt(result * result);
    }

    Point3D Point3D::operator+(Vector3D vec) const {
        return Point3D((_x + vec._x), (_y + vec._y), (_z + vec._z));
    }

    void Point3D::operator+=(const Vector3D vec) {
        _x += vec._x;
        _y += vec._y;
        _z += vec._z;
    }

    Point3D Point3D::operator-(Vector3D vec) const {
        return Point3D((_x - vec._x), (_y - vec._y), (_z - vec._z));
    }

    void Point3D::operator-=(const Vector3D vec) {
        _x -= vec._x;
        _y -= vec._y;
        _z -= vec._z;
    }


    Point3D Point3D::operator+(Point3D point) const {
        return Point3D((_x + point._x), (_y + point._y), (_z + point._z));
    }

    void Point3D::operator+=(const Point3D point) {
        _x += point._x;
        _y += point._y;
        _z += point._z;
    }

    Vector3D Point3D::operator-(const Point3D point) const {
        return Vector3D(_x - point._x, _y - point._y, _z - point._z);
    }

    void Point3D::operator-=(const Point3D point) {
        _x -= point._x;
        _y -= point._y;
        _z -= point._z;
    }

    bool Point3D::operator==(const Point3D point) const {
        if (_x == point._x && _y == point._y && _z == point._z)
            return true;
        return false;
    }

}