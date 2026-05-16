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
    Scene::Scene() = default;

    bool Scene::closestHit(const Ray &ray, double tMin, double tMax, HitRecord &record) const {
        double closest_so_far = tMax;
        bool hit_anything = false;
        HitRecord temp_record;

        for (const auto &obj : _objects) {
            if (obj->hits(ray, tMin, closest_so_far, temp_record)) {
                hit_anything = true;
                closest_so_far = temp_record.t;
                record = temp_record;
            }
        }

        return hit_anything;
    }

    void Scene::add_primitive(std::shared_ptr<IPrimitive> primitive) {
        _objects.push_back(std::move(primitive));
    }

    void Scene::add_light(std::shared_ptr<ILight> new_light) {
        _lights.push_back(std::move(new_light));
    }
}
