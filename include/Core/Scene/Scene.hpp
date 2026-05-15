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
    /**
     * @brief The Scene class stores all objects and lights.
     * 
     * It handles the logic for finding the closest intersection between
     * a ray and any object in the scene.
     */
    class Scene {
        public:
            Scene();
            ~Scene() = default;

            /**
             * @brief Find the closest intersection with any primitive in the scene.
             * 
             * @param ray The ray to trace.
             * @param tMin Minimum hit distance.
             * @param tMax Maximum hit distance.
             * @param record Output structure for hit information.
             * @return true if an object was hit.
             */
            bool closestHit(const Ray &ray, double tMin, double tMax, HitRecord &record) const;
            
            /** @brief Add a primitive to the scene. */
            void add_obj(std::shared_ptr<IPrimitive> obj);
            /** @brief Add a light source to the scene. */
            void add_light(std::shared_ptr<ILight> new_light);

            /** @return All objects in the scene. */
            const std::vector<std::shared_ptr<IPrimitive>>& getObjects() const { return _objects; }
            /** @return All light sources in the scene. */
            const std::vector<std::shared_ptr<ILight>>& getLights() const { return _lights; }

        private:
            std::vector<std::shared_ptr<IPrimitive>> _objects;
            std::vector<std::shared_ptr<ILight>> _lights;
    };
}

#endif /* SCENE_HPP */
