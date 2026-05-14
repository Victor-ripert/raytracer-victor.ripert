/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracer
*/

#include <cmath>
#include <iostream>
#include <memory>
#include "Core/Scene/Scene.hpp"
#include "Core/Render/Color.hpp"

namespace RayTracer {
    Scene::Scene() : light(nullptr) {}

    void Scene::hit_object(Ray ray_obj) {
        double distance_min = MAX_DISTANCE;
        bool any_hit = false;
        math::Point3D hit_pos;
        math::Vector3D surface_normal;
        Color color;
        Color new_color(0, 0, 0);
        Color final_color(0, 0, 0);
        math::Point3D candidate_pos;
        double new_distance = 0.0;

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
        for (const auto &l : lights) {
            new_color = compute_pixel(surface_normal, hit_pos, any_hit, color, l);
            final_color += new_color;
            // final_color /= 2;
            // if (new_color.r > final_color.r)
            //     final_color = new_color;
        }
        final_color.clampColor();
        std::cout << final_color.to_str() << std::endl;
    }

    Color Scene::compute_pixel(math::Vector3D surface_normal, math::Point3D hit_pos, bool any_hit, Color color, const std::shared_ptr<ILight> &current_light) {
        double light_angle = 0.0;
        // Color new_color = color;
        if (!any_hit) {
            return Color(0, 0, 0);
        } else if (current_light) {
            if (!hit_object_light(current_light, hit_pos)) {
                light_angle = getAngleFromLightAndSurface(surface_normal, current_light, hit_pos);
                light_angle /= 10;
                color.setShade(1 - light_angle);
                color.setShade(0.20);
            } else {
                light_angle = getAngleFromLightAndSurface(surface_normal, current_light, hit_pos);
                if (light_angle > 0.20)
                    color.setShade(light_angle);
                else {
                    color.setShade(0.20);
                }
            }
            return color;
        } else {
            // No light in scene, render flat color or black
            return color;
        }
    }

    bool Scene::hit_object_light(std::shared_ptr<ILight> l, math::Point3D target) {
        if (!l) return true;

        Ray ray_to_light = l->getRayToLight(target);
        double target_distance = l->getDistanceToLight(target);

        if (!l->isInLigthningWidth(ray_to_light._direction))
            return false;
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
        lights.push_back(std::move(new_light));
    }

    double Scene::getAngleFromLightAndSurface(math::Vector3D surfaceNormal,
        std::shared_ptr<ILight> l,
        math::Point3D surface) {
        if (!l) return 0.0;

        math::Vector3D light_direction = l->vectorSurfaceToLight(surface).normalize();
        double dot = light_direction.dot(surfaceNormal);
        return (dot < 0) ? 0 : dot;
    }
}
