/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracer nbootstrao
*/

#include "../include/materials/IMaterial.hpp"
#include "../include/transformations/ITransformation.hpp"
#include "../include/objects/Sphere.hpp"


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

    bool Sphere::hits_geometric(Ray ray_obj) {
        double t0 = 0.0;
        double t1 = 0.0;
        math::Vector3D L;
        double tca = 0.0;
        double d2 = 0.0;
        double thc = 0.0;

        L = _pos - ray_obj._origin;
        tca = L.dot(ray_obj._direction);
        d2 = L.dot(L) - tca * tca;
        if (d2 > _radius * _radius)
            return false;
        thc = sqrt(_radius * _radius - d2);
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

    bool Sphere::hits(const Ray &ray, double tMin, double tMax) const {
        Ray localRay;
        double t0 = 0.0;
        double t1 = 0.0;
        math::Vector3D L;
        double a = 0.0;
        double b = 0.0;
        double c = 0.0;
        double root = 0.0;
        math::Point3D local_hit;
        math::Vector3D outward_normal;
        double nd = 0.0;
        bool front_face = false;
        math::Vector3D local_normal;
        math::Point3D world_hit;
        math::Vector3D world_normal;

        localRay = _transform ? _transform->applyInverse(ray) : ray;

        L = localRay._origin - _pos;
        a = localRay._direction.dot(localRay._direction);
        b = 2 * localRay._direction.dot(L);
        c = L.dot(L) - _radius * _radius;
        if (!solveQuadratic(a, b, c, t0, t1))
            return false;

        if (t0 > t1)
            std::swap(t0, t1);
        root = t0;
        if (root < tMin) {
            root = t1;
            if (root < tMin)
                return false;
        }
        if (root > tMax)
            return false;

        local_hit = localRay._origin +
            (localRay._direction * root);
        outward_normal = local_hit - _pos;
        nd = outward_normal.dot(localRay._direction);
        front_face = nd < 0.0;
        local_normal = front_face ?
            outward_normal : outward_normal * (-1.0);

        world_hit = local_hit;
        world_normal = local_normal;
        if (_transform) {
            world_hit =
                _transform->transform_point_forward(local_hit);
            world_normal =
                _transform->transform_normal_forward(local_normal);
        }

        _last_hit_point = world_hit;
        _last_hit_normal = world_normal;
        return true;
    }

    math::Point3D Sphere::get_last_hit_point() const {
        return _last_hit_point;
    }

    math::Vector3D Sphere::get_last_hit_normal() const {
        return _last_hit_normal;
    }

    Color Sphere::get_last_hit_surface_color() const {
        return color;
    }

    std::shared_ptr<IMaterial> Sphere::getMaterial() const {
        return _material;
    }

    void Sphere::setMaterial(std::shared_ptr<IMaterial> material) {
        _material = std::move(material);
    }

    std::shared_ptr<ITransformation> Sphere::getTransform() const {
        return _transform;
    }

    void Sphere::setTransform(std::shared_ptr<ITransformation> transform) {
        _transform = std::move(transform);
    }

    std::string Sphere::getTypeName() const {
        return "sphere";
    }

    math::Point3D Sphere::getHitPoint(Ray ray_obj, double hit_distance)
    {
        return ray_obj._origin + (ray_obj._direction * hit_distance);
    }

    bool solveQuadratic(const double &a, const double &b, const double &c, double &x0, double &x1) {
        double q = 0.0;
        double discr = 0.0;

        if (std::abs(a) < 1e-12) {
            if (std::abs(b) < 1e-12)
                return false;
            x0 = x1 = -c / b;
            return true;
        }
        discr = b * b - 4 * a * c;
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
