/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracer
*/

#include <cmath>
#include <iostream>
#include <memory>
#include "../include/Core/Scene.hpp"
#include "../include/Core/Color.hpp"

namespace RayTracer {
    Scene::Scene() : light(nullptr) {}

    void Scene::hit_object(Ray ray_obj) {
        double distance_min = MAX_DISTANCE;
        bool any_hit = false;
        math::Point3D hit_pos;
        math::Vector3D surface_normal;
        Color color;
        math::Point3D candidate_pos;
        double new_distance = 0.0;
        double light_angle = 0.0;

        for (auto &obj : object_list) {
            if (!obj->hits(ray_obj, 1e-6, MAX_DISTANCE))
                continue;
            candidate_pos = obj->get_last_hit_point();
            new_distance = candidate_pos.distance_point(ray_obj._origin);
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
        } else if (light) {
            if (!hit_object_light(light, hit_pos)) {
                light_angle = getAngleFromLightAndSurface(surface_normal, light, hit_pos);
                color.setShade(1 - light_angle);
                color.setShade(0.20);
            } else {
                light_angle = getAngleFromLightAndSurface(surface_normal, light, hit_pos);
                color.setShade(1 - light_angle);
            }
            std::cout << color.to_str() << std::endl;
        } else {
            // No light in scene, render flat color or black
            std::cout << color.to_str() << std::endl;
        }
    }

    bool Scene::hit_object_light(std::shared_ptr<ILight> l, math::Point3D target) {
        if (!l) return true;
        
        Ray ray_to_light = l->getRayToLight(target);
        double target_distance = l->getDistanceToLight(target);

        for (auto &obj : object_list) {
            if (!obj->hits(ray_to_light, 1e-6, MAX_DISTANCE))
                continue;
            double new_distance = obj->get_last_hit_point().distance_point(target);
            if (new_distance < target_distance - 1e-6)
                return false;
        }
        return true;
    }

    void Scene::add_obj(std::shared_ptr<IPrimitive> obj) {
        object_list.push_back(obj);
    }

    void Scene::add_light(std::shared_ptr<ILight> new_light) {
        light = new_light;
    }

    double Scene::getAngleFromLightAndSurface(math::Vector3D surfaceNormal,
        std::shared_ptr<ILight> l,
        math::Point3D surface) {
        if (!l) return 0.0;
        
        math::Vector3D light_direction = math::Vector3D(l->getPosition() - surface).normalize();
        double dot = light_direction.dot(surfaceNormal);
        return (dot < 0) ? 0 : dot;
    }
}
