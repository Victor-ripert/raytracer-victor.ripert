/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Raytracing_bootstrap
*/

#include "../../include/Math/Vector3D.hpp"
#include "../../include/Math/Point3D.hpp"

namespace math {
    Vector3D::Vector3D() {
        _x = 0;
        _y = 0;
        _z = 0;
    }

    Vector3D::Vector3D(double x, double y, double z) : _x(x), _y(y), _z(z) {}

    Vector3D::Vector3D(Point3D point) : _x(point._x), _y(point._y), _z(point._z) {}

    void Vector3D::display() {
        std::cout << "Vector3D(" << _x << ", " << _y << ", " << _z << ")" << std::endl;
    }

    double Vector3D::length() const {
        return sqrt(_x * _x + _y * _y + _z * _z);
    }

    double Vector3D::dot(const Vector3D &vec) const {
        return _x * vec._x + _y * vec._y + _z * vec._z;
    }

    double Vector3D::angle(const Vector3D &vec) const {
        double len1 = this->length();
        double len2 = this->length();
        double cosValue;

        if (len1 == 0.0 || len2 == 0.0)
            return 0.00;
        cosValue = this->dot(vec) / (len1 * len2);
        if (cosValue > 1.0)
            cosValue = 1.0;
        else if (cosValue < -1.0)
            cosValue = -1.0;
        return std::acos(cosValue) * 180.0 / M_PI;
    }

    Vector3D Vector3D::normalize() {
        double len = length();
        if (len > 0) {
            _x /= len;
            _y /= len;
            _z /= len;
        }
        return *this;
    }

    Vector3D Vector3D::operator+(const Vector3D vec) const {
        return Vector3D(_x + vec._x, _y + vec._y, _z + vec._z);
    }

    void Vector3D::operator+=(const Vector3D vec) {
        _x += vec._x;
        _y += vec._y;
        _z += vec._z;
    }

    Vector3D Vector3D::operator-(const Vector3D vec) const {
        return Vector3D(_x - vec._x, _y - vec._y, _z - vec._z);
    }

    void Vector3D::operator-=(const Vector3D vec) {
        _x -= vec._x;
        _y -= vec._y;
        _z -= vec._z;
    }

    Vector3D Vector3D::operator*(const Vector3D vec) const {
        return Vector3D(_x * vec._x, _y * vec._y, _z * vec._z);
    }

    Vector3D Vector3D::operator*(double nb) const {
        return Vector3D(_x * nb, _y * nb, _z * nb);
    }

    void Vector3D::operator*=(const Vector3D vec) {
        _x *= vec._x;
        _y *= vec._y;
        _z *= vec._z;
    }

    void Vector3D::operator*=(double nb) {
        _x *= nb;
        _y *= nb;
        _z *= nb;
    }

    Vector3D Vector3D::operator/(const Vector3D vec) const {
        return Vector3D(_x / vec._x, _y / vec._y, _z / vec._z);
    }

    Vector3D Vector3D::operator/(double nb) const {
        return Vector3D(_x / nb, _y / nb, _z / nb);
    }

    void Vector3D::operator/=(const Vector3D vec) {
        _x /= vec._x;
        _y /= vec._y;
        _z /= vec._z;
    }

    void Vector3D::operator/=(double nb) {
        _x /= nb;
        _y /= nb;
        _z /= nb;
    }
}
