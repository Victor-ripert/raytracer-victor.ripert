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
#include "../../API/IPrimitive.hpp"
#include "../../API/ILight.hpp"
#include "../Constants.hpp"

namespace RayTracer {
    class Scene {
        public:
            Scene();
            ~Scene() = default;

            bool closestHit(const Ray &ray, double tMin, double tMax, HitRecord &record) const;
            
            void add_obj(std::shared_ptr<IPrimitive> obj);
            void add_light(std::shared_ptr<ILight> new_light);

            const std::vector<std::shared_ptr<IPrimitive>>& getObjects() const { return _objects; }
            const std::vector<std::shared_ptr<ILight>>& getLights() const { return _lights; }

        private:
            std::vector<std::shared_ptr<IPrimitive>> _objects;
            std::vector<std::shared_ptr<ILight>> _lights;
    };
}

#endif /* SCENE_HPP */
