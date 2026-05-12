/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Plane Plugin Implementation
*/

#include "API/ITransformation.hpp"
#include "Plane.hpp"

namespace RayTracer {
    Plane::Plane() : _point(math::Point3D()), _normal(math::Vector3D(0, 1, 0)), color(Color(128, 128, 128)) {}

    Plane::Plane(const math::Point3D &point, const math::Vector3D &normal, const Color &col)
        : _point(point), _normal(normal), color(col) {}

    void Plane::applyConfig(const PrimitiveConfig &config)
    {
        _point = config.position;
        math::Vector3D normalVector = config.normal;
        normalVector.normalize();
        _normal = normalVector;
        color = config.color;
    }

    bool Plane::hits(const Ray &ray, double tMin, double tMax) const {
        Ray localRay = _transform ? _transform->applyInverse(ray) : ray;
        double denom = _normal.dot(localRay._direction);
        if (std::abs(denom) < 1e-12) return false;

        double t = (_point - localRay._origin).dot(_normal) / denom;
        if (t < tMin || t > tMax) return false;

        math::Point3D local_hit = localRay._origin + (localRay._direction * t);
        bool front_face = _normal.dot(localRay._direction) < 0;
        math::Vector3D local_normal = front_face ? _normal : _normal * (-1.0);

        _last_hit_point = _transform ? _transform->transform_point_forward(local_hit) : local_hit;
        _last_hit_normal = _transform ? _transform->transform_normal_forward(local_normal) : local_normal;
        return true;
    }

    math::Point3D Plane::get_last_hit_point() const { return _last_hit_point; }
    math::Vector3D Plane::get_last_hit_normal() const { return _last_hit_normal; }
    Color Plane::get_last_hit_surface_color() const { return color; }
    std::shared_ptr<ITransformation> Plane::getTransform() const { return _transform; }
    void Plane::setTransform(std::shared_ptr<ITransformation> transform) { _transform = std::move(transform); }
    std::string Plane::getTypeName() const { return "plane"; }
}

extern "C" RayTracer::IPrimitive* create_primitive() {
    return new RayTracer::Plane();
}

extern "C" void destroy_primitive(RayTracer::IPrimitive* primitive) {
    delete primitive;
}
