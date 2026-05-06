/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracer
*/

#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include <memory>
#include <string>
#include "../Core/Render/Color.hpp"
#include "../Math/Ray.hpp"
#include "PrimitiveConfig.hpp"

namespace RayTracer {

    class IMaterial;
    class ITransformation;

    class IPrimitive {
    public:
        virtual ~IPrimitive() = default;

        virtual void applyConfig(const PrimitiveConfig &config) = 0;

        virtual bool hits(const Ray &ray, double tMin, double tMax) const = 0;

        virtual math::Point3D get_last_hit_point() const = 0;
        virtual math::Vector3D get_last_hit_normal() const = 0;
        virtual Color get_last_hit_surface_color() const = 0;

        virtual std::shared_ptr<IMaterial> getMaterial() const = 0;

        virtual void setMaterial(std::shared_ptr<IMaterial> material) = 0;

        virtual std::shared_ptr<ITransformation> getTransform() const = 0;

        virtual void setTransform(std::shared_ptr<ITransformation> transform) = 0;

        virtual std::string getTypeName() const = 0;
    };

}

#endif /* IOBJECT_HPP */
