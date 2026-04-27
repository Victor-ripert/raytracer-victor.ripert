/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracer
*/


#include "../include/Scene.hpp"
#include "../include/Color.hpp"
#include "../include/Sphere.hpp"

namespace RayTracer {
    Scene::Scene() {}

    Scene::~Scene() {}

    void Scene::hit_object(Ray ray_obj) {
        double distance_min = MAX_DISTANCE;
        double new_distance = 0;
        math::Point3D hit_pos;
        math::Vector3D surface_normal;
        Color color;
        for (auto obj : object_list) {
            if (obj->hits(ray_obj)) {
                new_distance = obj->get_last_hit_point().distance_point(ray_obj._origin);
                if (hit_pos == math::Point3D(0, 0, 0))
                    hit_pos = obj->get_last_hit_point();
                if (new_distance < distance_min) {
                    distance_min = new_distance;
                    color = obj->get_color();
                    hit_pos = obj->get_last_hit_point();
                    surface_normal = obj->getNormalFromPointOnSphere(hit_pos);
                }
            }
        }
        if (distance_min >= MAX_DISTANCE) {
            std::cout << "0 0 0" << std::endl;
        } else {
            if (!hit_object_light(light, hit_pos)) {
                double light_angle = getAngleFromLightAndSurface(surface_normal, light, hit_pos);
                color.setShade(1 - light_angle);
                color.setShade(0.20);
                // color = Color(0, 0, 0);
            } else {
                double light_angle = getAngleFromLightAndSurface(surface_normal, light, hit_pos);
                color.setShade(1 - light_angle);
            }
            std::cout << color.to_str() << std::endl;
        }
    }

    bool Scene::hit_object_light(AmbiantLight l, math::Point3D target) {
        Ray ray_obj = l.ray(target);
        double target_distance = target.distance_point(l.origin);
        double new_distance = 0;
        math::Point3D hit_pos;
        for (auto obj : object_list) {
            if (obj->hits(ray_obj)) {
                hit_pos = obj->get_last_hit_point();
                new_distance = hit_pos.distance_point(l.origin);
                if (new_distance + 1e-6 < target_distance)
                    return false;
            }
        }
        return true;
    }

    void Scene::add_obj(IObject *obj) {
        object_list.push_back(obj);
    }

    void Scene::add_light(AmbiantLight new_light) {
        light = new_light;
    }

    double Scene::getAngleFromLightAndSurface(math::Vector3D surfaceNormal, AmbiantLight l, math::Point3D surface) {
        math::Vector3D light_direction = surface - l.origin;
        return light_direction.dot(surfaceNormal);
    }
}