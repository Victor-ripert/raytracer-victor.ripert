/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracer
*/


#include <cmath>
#include "../include/Scene.hpp"
#include "../include/Color.hpp"
#include "../include/objects/Sphere.hpp"

namespace RayTracer {
    Scene::Scene() {}

    Scene::~Scene() {}

    void Scene::hit_object(Ray ray_obj) {
        double distance_min = MAX_DISTANCE;
        bool any_hit = false;
        math::Point3D hit_pos;
        math::Vector3D surface_normal;
        Color color;
        math::Point3D candidate_pos;
        double new_distance = 0.0;
        double light_angle = 0.0;

        for (auto obj : object_list) {
            if (!obj->hits(ray_obj, 1e-6, MAX_DISTANCE))
                continue;
            candidate_pos = obj->get_last_hit_point();
            new_distance =
                candidate_pos.distance_point(ray_obj._origin);
            if (!any_hit || new_distance < distance_min) {
                any_hit = true;
                distance_min = new_distance;
                hit_pos = candidate_pos;
                surface_normal = obj->get_last_hit_normal();
                color = obj->get_last_hit_surface_color();
            }
        }
        if (!any_hit) {
            std::cout << "0 0 0" << std::endl;
        } else {
            if (!hit_object_light(light, hit_pos)) {
                light_angle =
                    getAngleFromLightAndSurface(surface_normal,
                        light,
                        hit_pos);
                color.setShade(1 - light_angle);
                color.setShade(0.20);
                // color = Color(0, 0, 0);
            } else {
                light_angle =
                    getAngleFromLightAndSurface(surface_normal,
                        light,
                        hit_pos);
                color.setShade(1 - light_angle);
            }
            std::cout << color.to_str() << std::endl;
        }
    }

    bool Scene::hit_object_light(AmbientLight l, math::Point3D target) {
        Ray ray_obj;
        double target_distance = 0.0;
        double new_distance = 0.0;

        ray_obj = l.ray(target);
        target_distance = target.distance_point(l.origin);
        for (auto obj : object_list) {
            if (!obj->hits(ray_obj, 1e-6, MAX_DISTANCE))
                continue;
            new_distance = obj->get_last_hit_point().distance_point(
                l.origin);
            if (new_distance + 1e-6 < target_distance)
                return false;
        }
        return true;
    }

    void Scene::add_obj(IObject *obj) {
        object_list.push_back(obj);
    }

    void Scene::add_light(AmbientLight new_light) {
        light = new_light;
    }

    double Scene::getAngleFromLightAndSurface(math::Vector3D surfaceNormal,
        AmbientLight l,
        math::Point3D surface) {
        math::Vector3D light_direction;

        light_direction = surface - l.origin;
        return light_direction.dot(surfaceNormal);
    }
}
