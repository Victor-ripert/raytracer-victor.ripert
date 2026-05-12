/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Sphere Plugin Implementation
*/

#include "API/ITransformation.hpp"
#include "Sphere.hpp"

namespace RayTracer {
    Sphere::Sphere() {
        _pos = math::Point3D();
        _radius = 1;
        color = Color(255, 0, 0);
    }

    Sphere::Sphere(math::Point3D pos, double radius, Color color) : _pos(pos), _radius(radius), color(color) {}

    void Sphere::applyConfig(const PrimitiveConfig &config)
    {
        _pos = config.position;
        _radius = config.radius;
        color = config.color;
    }

    bool Sphere::hits(const Ray &ray, double tMin, double tMax) const {
        Ray localRay = _transform ? _transform->applyInverse(ray) : ray;
        math::Vector3D L = localRay._origin - _pos;
        double a = localRay._direction.dot(localRay._direction);
        double b = 2 * localRay._direction.dot(L);
        double c = L.dot(L) - _radius * _radius;
        double t0, t1;

        if (!solveQuadratic(a, b, c, t0, t1)) return false;
        if (t0 > t1) std::swap(t0, t1);
        double root = t0;
        if (root < tMin) {
            root = t1;
            if (root < tMin) return false;
        }
        if (root > tMax) return false;

        math::Point3D local_hit = localRay._origin + (localRay._direction * root);
        math::Vector3D outward_normal = local_hit - _pos;
        bool front_face = outward_normal.dot(localRay._direction) < 0;
        math::Vector3D local_normal = front_face ? outward_normal : outward_normal * (-1.0);

        _last_hit_point = _transform ? _transform->transform_point_forward(local_hit) : local_hit;
        _last_hit_normal = _transform ? _transform->transform_normal_forward(local_normal) : local_normal;
        return true;
    }

    math::Point3D Sphere::get_last_hit_point() const { return _last_hit_point; }
    math::Vector3D Sphere::get_last_hit_normal() const { return _last_hit_normal; }
    Color Sphere::get_last_hit_surface_color() const { return color; }
    std::shared_ptr<ITransformation> Sphere::getTransform() const { return _transform; }
    void Sphere::setTransform(std::shared_ptr<ITransformation> transform) { _transform = std::move(transform); }
    std::string Sphere::getTypeName() const { return "sphere"; }

    bool solveQuadratic(const double &a, const double &b, const double &c, double &x0, double &x1) {
        double discr = b * b - 4 * a * c;
        if (discr < 0) return false;
        if (discr == 0) x0 = x1 = -0.5 * b / a;
        else {
            double q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
            x0 = q / a;
            x1 = c / q;
        }
        if (x0 > x1) std::swap(x0, x1);
        return true;
    }
}

extern "C" RayTracer::IPrimitive* create_primitive() {
    return new RayTracer::Sphere();
}

extern "C" void destroy_primitive(RayTracer::IPrimitive* primitive) {
    delete primitive;
}
