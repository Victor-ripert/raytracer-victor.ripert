/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracer
*/


#ifndef IOBJECT_HPP
    #define IOBJECT_HPP
    #include "Ray.hpp"
    #include "Color.hpp"

namespace RayTracer {
    class IObject {
        public:
            virtual bool hits(Ray ray_obj) = 0;
            virtual math::Point3D get_center() = 0;
            virtual Color get_color() = 0;
            virtual math::Point3D get_last_hit_point() = 0;
            virtual math::Vector3D getNormalFromPointOnSphere(math::Point3D point) = 0;
    };
}

#endif /* IOBJECT_HPP */