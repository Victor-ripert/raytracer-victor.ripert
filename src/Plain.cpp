/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Raytracer
*/

#include "../include/Plain.hpp"

namespace RayTracer {
    Plain::Plain() {
        center = math::Point3D();
        orientation = math::Vector3D();
    }

    Plain::Plain(math::Point3D pos, math::Vector3D ori) : center(pos), orientation(ori) {}

    bool intersectPlane(math::Vector3D &n, const math::Point3D &p0, const math::Vector3D &l0, const math::Vector3D &l) {
        double denom = n.dot(l);
        if (denom > 1e-6) {
            math::Vector3D p0l0 = p0 - l0;
            double t = p0l0.dot(n) / denom;
            return (t >= 0);
        }
        return false;
    }

    bool Plain::hits(RayTracer::Ray ray_obj) {
        return intersectPlane(orientation, center, ray_obj._origin, ray_obj._direction);
    }
}