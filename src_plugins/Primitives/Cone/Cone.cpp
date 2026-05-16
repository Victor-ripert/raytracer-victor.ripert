/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** Cone Plugin Implementation
*/

#include "API/ITransformation.hpp"
#include "Cone.hpp"
#include "Core/Config/ConfigUtils.hpp"
#include "Core/Constants.hpp"

namespace RayTracer {
    Cone::Cone() {
        _pos = math::Point3D();
        _radius = 1;
        _height = 2;
        _color = Color(0, 0, 255);
    }

    Cone::Cone(math::Point3D pos, double radius, double height, Color color)
        : _pos(pos), _radius(radius), _height(height), _color(color) {}

    void Cone::applyConfig(const libconfig::Setting &node)
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

    bool Cone::hits(const Ray &ray, double tMin, double tMax, HitRecord &record) const {
        Ray localRay = _transform ? _transform->applyInverse(ray) : ray;
        
        double k = (_radius / _height) * (_radius / _height);
        math::Vector3D oc = localRay._origin - _pos;
        
        double a = localRay._direction._x * localRay._direction._x + 
                   localRay._direction._z * localRay._direction._z - 
                   k * localRay._direction._y * localRay._direction._y;
        double b = 2.0 * (oc._x * localRay._direction._x + 
                          oc._z * localRay._direction._z - 
                          k * oc._y * localRay._direction._y);
        double c = oc._x * oc._x + oc._z * oc._z - k * oc._y * oc._y;

        double t0, t1;
        double root = -1.0;
        math::Vector3D normal;
        bool hit = false;

        if (solveQuadratic(a, b, c, t0, t1)) {
            if (t0 > t1) std::swap(t0, t1);

            double y_min = std::min(_pos._y, _pos._y + _height);
            double y_max = std::max(_pos._y, _pos._y + _height);

            double y0 = localRay._origin._y + t0 * localRay._direction._y;
            if (t0 >= tMin && t0 <= tMax && y0 >= y_min && y0 <= y_max) {
                root = t0;
                double dy = y0 - _pos._y;
                normal = math::Vector3D(localRay._origin._x + t0 * localRay._direction._x - _pos._x, -k * dy, localRay._origin._z + t0 * localRay._direction._z - _pos._z);
                hit = true;
            }

            if (!hit) {
                double y1 = localRay._origin._y + t1 * localRay._direction._y;
                if (t1 >= tMin && t1 <= tMax && y1 >= y_min && y1 <= y_max) {
                    root = t1;
                    double dy = y1 - _pos._y;
                    normal = math::Vector3D(localRay._origin._x + t1 * localRay._direction._x - _pos._x, -k * dy, localRay._origin._z + t1 * localRay._direction._z - _pos._z);
                    hit = true;
                }
            }
        }

        // Check base cap
        double t_cap = (_pos._y + _height - localRay._origin._y) / localRay._direction._y;
        if (t_cap >= tMin && t_cap <= tMax && (root < 0 || t_cap < root)) {
            math::Point3D p = localRay._origin + localRay._direction * t_cap;
            if ((p._x - _pos._x) * (p._x - _pos._x) + (p._z - _pos._z) * (p._z - _pos._z) <= _radius * _radius) {
                root = t_cap;
                normal = math::Vector3D(0, (_height > 0 ? 1 : -1), 0);
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

    std::shared_ptr<ITransformation> Cone::getTransform() const { return _transform; }
    void Cone::setTransform(std::shared_ptr<ITransformation> transform) { _transform = std::move(transform); }
    std::string Cone::getTypeName() const { return "cone"; }

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
    return new RayTracer::Cone();
}

extern "C" void destroy_primitive(RayTracer::IPrimitive* primitive) {
    delete primitive;
}

extern "C" const char* get_type() {
    return "cone";
}
