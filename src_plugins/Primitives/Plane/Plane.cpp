/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Plane Plugin Implementation
*/

#include "API/ITransformation.hpp"
#include "Plane.hpp"
#include "Core/Config/ConfigUtils.hpp"
#include "Core/Constants.hpp"

namespace RayTracer {
    Plane::Plane() : _point(math::Point3D()), _normal(math::Vector3D(0, 1, 0)), _color(Color(128, 128, 128)) {}

    Plane::Plane(const math::Point3D &point, const math::Vector3D &normal, const Color &col)
        : _point(point), _normal(normal), _color(col) {}

    void Plane::applyConfig(const libconfig::Setting &node)
    {
        if (node.exists("point")) {
            _point = ConfigUtils::readPoint3(node["point"]);
        } else if (node.exists("position")) {
            _point = ConfigUtils::readPoint3(node["position"]);
        }

        if (node.exists("normal")) {
            _normal = ConfigUtils::readVector3(node["normal"]);
            _normal.normalize();
        }

        if (node.exists("color")) {
            _color = ConfigUtils::readColor(node["color"]);
        }
    }

    bool Plane::hits(const Ray &ray, double tMin, double tMax, HitRecord &record) const {
        Ray localRay = _transform ? _transform->applyInverse(ray) : ray;
        double denom = _normal.dot(localRay._direction);
        if (std::abs(denom) < EPSILON) return false;

        double t = (_point - localRay._origin).dot(_normal) / denom;
        if (t < tMin || t > tMax) return false;

        math::Point3D local_hit = localRay._origin + (localRay._direction * t);
        bool front_face = _normal.dot(localRay._direction) < 0;
        math::Vector3D local_normal = front_face ? _normal : _normal * (-1.0);

        record.t = t;
        record.hit_point = _transform ? _transform->transform_point_forward(local_hit) : local_hit;
        record.normal = _transform ? _transform->transform_normal_forward(local_normal) : local_normal;
        record.color = _color;
        record.material = _material;
        return true;
    }

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

extern "C" const char* get_type() {
    return "plane";
}
