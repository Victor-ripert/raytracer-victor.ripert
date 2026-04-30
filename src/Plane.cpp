/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Plane
*/

#include "../include/materials/IMaterial.hpp"
#include "../include/transformations/ITransformation.hpp"
#include "../include/objects/Plane.hpp"

namespace RayTracer {

    Plane::Plane()
    {
        _point = math::Point3D();
        _normal = math::Vector3D(0, 1, 0);
        color = Color(128, 128, 128);
    }

    Plane::Plane(const math::Point3D &point, const math::Vector3D &normal, const Color &col)
        : _point(point), _normal(normal), color(col)
    {
    }

    void Plane::display()
    {
        std::cout << "Plane: point ";
        _point.display();
        std::cout << " normal ";
        _normal.display();
        std::cout << std::endl;
    }

    bool Plane::hits(const Ray &ray, double tMin, double tMax) const
    {
        Ray localRay = _transform ? _transform->applyInverse(ray) : ray;

        math::Vector3D n = _normal;
        double nlen = n.length();
        if (nlen < 1e-12)
            return false;

        math::Vector3D unit_n = n * (1.0 / nlen);
        math::Vector3D p0_minus_o(_point - localRay._origin);
        double denom = unit_n.dot(localRay._direction);

        if (std::abs(denom) < 1e-12)
            return false;

        double t = unit_n.dot(p0_minus_o) / denom;
        if (t < tMin || t > tMax)
            return false;

        math::Point3D local_hit = localRay._origin + (localRay._direction * t);
        math::Vector3D outward_normal = unit_n;
        double nd = outward_normal.dot(localRay._direction);
        bool front_face = nd < 0.0;
        math::Vector3D local_normal = front_face ? outward_normal : outward_normal * (-1.0);

        math::Point3D world_hit = local_hit;
        math::Vector3D world_normal = local_normal;
        if (_transform) {
            world_hit = _transform->transform_point_forward(local_hit);
            world_normal = _transform->transform_normal_forward(local_normal);
        }

        _last_hit_point = world_hit;
        _last_hit_normal = world_normal;
        return true;
    }

    math::Point3D Plane::get_last_hit_point() const
    {
        return _last_hit_point;
    }

    math::Vector3D Plane::get_last_hit_normal() const
    {
        return _last_hit_normal;
    }

    Color Plane::get_last_hit_surface_color() const
    {
        return color;
    }

    std::shared_ptr<IMaterial> Plane::getMaterial() const
    {
        return _material;
    }

    void Plane::setMaterial(std::shared_ptr<IMaterial> material)
    {
        _material = std::move(material);
    }

    std::shared_ptr<ITransformation> Plane::getTransform() const
    {
        return _transform;
    }

    void Plane::setTransform(std::shared_ptr<ITransformation> transform)
    {
        _transform = std::move(transform);
    }

    std::string Plane::getTypeName() const
    {
        return "plane";
    }

}
