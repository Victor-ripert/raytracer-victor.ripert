/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** Cylinder Plugin Implementation
*/

#include "API/ITransformation.hpp"
#include "Cylinder.hpp"
#include "Core/Config/ConfigUtils.hpp"
#include "Core/Constants.hpp"

namespace RayTracer {
    Cylinder::Cylinder() {
        _pos = math::Point3D();
        _radius = 1;
        _height = 2;
        _color = Color(0, 255, 0);
    }

    Cylinder::Cylinder(math::Point3D pos, double radius, double height, Color color)
        : _pos(pos), _radius(radius), _height(height), _color(color) {}

    void Cylinder::applyConfig(const libconfig::Setting &node)
    {
        if (node.exists("position")) {
            _pos = ConfigUtils::readPoint3(node["position"]);
        }

        ConfigUtils::tryReadDouble(node, "radius", _radius);
        ConfigUtils::tryReadDouble(node, "height", _height);

        if (node.exists("color")) {
            _color = ConfigUtils::readColor(node["color"]);
        }
    }

    bool Cylinder::hits(const Ray &ray, double tMin, double tMax, HitRecord &record) const {
        Ray localRay = _transform ? _transform->applyInverse(ray) : ray;
        
        math::Vector3D oc = localRay._origin - _pos;
        double a = localRay._direction._x * localRay._direction._x + localRay._direction._z * localRay._direction._z;
        double b = 2.0 * (oc._x * localRay._direction._x + oc._z * localRay._direction._z);
        double c = oc._x * oc._x + oc._z * oc._z - _radius * _radius;

        double t0, t1;
        double root = -1.0;
        math::Vector3D normal;
        bool hit = false;

        if (solveQuadratic(a, b, c, t0, t1)) {
            if (t0 > t1) std::swap(t0, t1);

            double y0 = localRay._origin._y + t0 * localRay._direction._y;
            if (y0 >= _pos._y - _height / 2.0 && y0 <= _pos._y + _height / 2.0) {
                if (t0 >= tMin && t0 <= tMax) {
                    root = t0;
                    math::Point3D local_hit = localRay._origin + (localRay._direction * root);
                    normal = math::Vector3D(local_hit._x - _pos._x, 0, local_hit._z - _pos._z);
                    hit = true;
                }
            }
            
            if (!hit) {
                double y1 = localRay._origin._y + t1 * localRay._direction._y;
                if (y1 >= _pos._y - _height / 2.0 && y1 <= _pos._y + _height / 2.0) {
                    if (t1 >= tMin && t1 <= tMax) {
                        root = t1;
                        math::Point3D local_hit = localRay._origin + (localRay._direction * root);
                        normal = math::Vector3D(local_hit._x - _pos._x, 0, local_hit._z - _pos._z);
                        hit = true;
                    }
                }
            }
        }

        double t_cap_bottom = (_pos._y - _height / 2.0 - localRay._origin._y) / localRay._direction._y;
        if (t_cap_bottom >= tMin && t_cap_bottom <= tMax && (root < 0 || t_cap_bottom < root)) {
            math::Point3D p = localRay._origin + localRay._direction * t_cap_bottom;
            if ((p._x - _pos._x) * (p._x - _pos._x) + (p._z - _pos._z) * (p._z - _pos._z) <= _radius * _radius) {
                root = t_cap_bottom;
                normal = math::Vector3D(0, -1, 0);
                hit = true;
            }
        }

        double t_cap_top = (_pos._y + _height / 2.0 - localRay._origin._y) / localRay._direction._y;
        if (t_cap_top >= tMin && t_cap_top <= tMax && (root < 0 || t_cap_top < root)) {
            math::Point3D p = localRay._origin + localRay._direction * t_cap_top;
            if ((p._x - _pos._x) * (p._x - _pos._x) + (p._z - _pos._z) * (p._z - _pos._z) <= _radius * _radius) {
                root = t_cap_top;
                normal = math::Vector3D(0, 1, 0);
                hit = true;
            }
        }

        if (!hit) return false;

        normal.normalize();
        bool front_face = normal.dot(localRay._direction) < 0;
        if (!front_face) normal = normal * (-1.0);

        record.t = root;
        math::Point3D local_hit = localRay._origin + (localRay._direction * root);
        record.hit_point = _transform ? _transform->transform_point_forward(local_hit) : local_hit;
        record.normal = _transform ? _transform->transform_normal_forward(normal) : normal;
        record.color = _color;
        record.material = _material;
        return true;
    }

    std::shared_ptr<ITransformation> Cylinder::getTransform() const { return _transform; }
    void Cylinder::setTransform(std::shared_ptr<ITransformation> transform) { _transform = std::move(transform); }
    std::string Cylinder::getTypeName() const { return "cylinder"; }

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
    return new RayTracer::Cylinder();
}

extern "C" void destroy_primitive(RayTracer::IPrimitive* primitive) {
    delete primitive;
}

extern "C" const char* get_type() {
    return "cylinder";
}
