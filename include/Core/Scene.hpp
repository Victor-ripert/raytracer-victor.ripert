/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracer
*/

#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include "../API/IPrimitive.hpp"
#include "../API/ILight.hpp"

#define MAX_DISTANCE 1000

namespace RayTracer {
    class Scene {
        public:
            std::vector<std::shared_ptr<IPrimitive>> object_list;
            std::shared_ptr<ILight> light; // Now using the Interface

            Scene();
            ~Scene() = default;

            void hit_object(Ray ray_obj);
            bool hit_object_light(std::shared_ptr<ILight> l, math::Point3D target);
            void add_obj(std::shared_ptr<IPrimitive> obj);
            void add_light(std::shared_ptr<ILight> new_light);
            double getAngleFromLightAndSurface(math::Vector3D surfaceNormal, std::shared_ptr<ILight> l, math::Point3D surface);
    };
}

#endif /* SCENE_HPP */
