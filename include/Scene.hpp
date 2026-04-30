/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracer
*/


#ifndef SCENE_HPP
    #define SCENE_HPP
    #include <vector>
    #include "objects/IObject.hpp"
    #include "AmbientLight.hpp"
    #define MAX_DISTANCE 1000

namespace RayTracer {
    class Scene {
        public:
        std::vector <IObject *> object_list;
        AmbientLight light;
        Scene();
        ~Scene();
        void hit_object(Ray ray_obj);
        bool hit_object_light(AmbientLight l, math::Point3D target);
        void add_obj(IObject *obj);
        void add_light(AmbientLight new_light);
        double getAngleFromLightAndSurface(math::Vector3D surfaceNormal, AmbientLight l, math::Point3D surface);
    };
}

#endif /* SCENE_HPP */
