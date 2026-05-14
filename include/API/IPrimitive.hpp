/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracer
*/

#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include <libconfig.h++>
#include <memory>
#include <string>
#include "../Core/Render/Color.hpp"
#include "../Math/Ray.hpp"

namespace RayTracer {

    class IMaterial;
    class ITransformation;

    struct HitRecord {
        double t;
        math::Point3D hit_point;
        math::Vector3D normal;
        Color color;
        std::shared_ptr<IMaterial> material;
    };

    class IPrimitive {
    public:
        virtual ~IPrimitive() = default;

        virtual void applyConfig(const libconfig::Setting &node) = 0;

        virtual bool hits(const Ray &ray, double tMin, double tMax, HitRecord &record) const = 0;

        virtual std::shared_ptr<IMaterial> getMaterial() const = 0;

        virtual void setMaterial(std::shared_ptr<IMaterial> material) = 0;

        virtual std::shared_ptr<ITransformation> getTransform() const = 0;

        virtual void setTransform(std::shared_ptr<ITransformation> transform) = 0;

        virtual std::string getTypeName() const = 0;
    };

}

#endif /* IOBJECT_HPP */
