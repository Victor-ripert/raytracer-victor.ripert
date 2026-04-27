/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracer nbootstrao
*/

#include "../include/Sphere.hpp"


namespace RayTracer {
    Sphere::Sphere() {
        _pos = math::Point3D();
        _radius = 1;
        color = Color(255, 0, 0);
    }

    Sphere::Sphere(math::Point3D pos, double radius, Color color) : _pos(pos), _radius(radius), color(color) {}

    void Sphere::display() {
        std::cout << "Sphere(\n\t";
        _pos.display();
        std::cout << ",\n\t radius: " << _radius << std::endl;
    }

    math::Point3D Sphere::get_center() {
        return _pos;
    }

    Color Sphere::get_color() {
        return color;
    }

    math::Point3D Sphere::get_last_hit_point() {
        return _last_hit_point;
    }

    bool Sphere::hits_geometric(Ray ray_obj) {
        double t0, t1;

        math::Vector3D L = _pos - ray_obj._origin;
        double tca = L.dot(ray_obj._direction);
        double d2 = L.dot(L) - tca * tca;
        if (d2 > _radius * _radius)
            return false;
        double thc = sqrt(_radius * _radius - d2);
        t0 = tca - thc;
        t1 = tca + thc;

        if (t0 > t1)
            std::swap(t0, t1);
        if (t0 < 0) {
            t0 = t1;
            if (t0 < 0)
            return false;
        }
        return true;
    }

    bool Sphere::hits(Ray ray_obj) {
        double t0, t1;
        math::Vector3D L = ray_obj._origin - _pos;
        double a = ray_obj._direction.dot(ray_obj._direction);
        double b = 2 * ray_obj._direction.dot(L);
        double c = L.dot(L) - _radius * _radius;
        if (!solveQuadratic(a, b, c, t0, t1))
            return false;

        if (t0 > t1)
            std::swap(t0, t1);
        if (t0 < 0) {
            t0 = t1;
            if (t0 < 0)
            return false;
        }
        _last_hit_point = ray_obj._origin + (ray_obj._direction * t0);
        return true;
    }

    math::Point3D Sphere::getHitPoint(Ray ray_obj, double hit_distance)
    {
        return ray_obj._origin + (ray_obj._direction * hit_distance);
    }

    bool solveQuadratic(const double &a, const double &b, const double &c, double &x0, double &x1) {
        if (std::abs(a) < 1e-12) {
            if (std::abs(b) < 1e-12)
                return false;
            x0 = x1 = -c / b;
            return true;
        }
        double q;
        double discr = b * b - 4 * a * c;
        if (discr < 0)
            return false;
        else if (discr == 0)
            x0 = x1 = -0.5 * b / a;
        else {
            q = (b > 0) ?
                -0.5 * (b + sqrt(discr)) :
                -0.5 * (b - sqrt(discr));
            x0 = q / a;
            x1 = c / q;
        }
        if (x0 > x1)
            std::swap(x0, x1);
        return true;
    }

    math::Vector3D Sphere::getNormalFromPointOnSphere(math::Point3D point) {
        return point - _pos;
    }
}
