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

    /**
     * @brief Structure representing the intersection of a ray with a primitive.
     */
    struct HitRecord {
        double t;                           /**< Ray parameter at intersection */
        math::Point3D hit_point;           /**< Coordinates of the hit point */
        math::Vector3D normal;             /**< Normal vector at the hit point */
        Color color;                        /**< Surface color of the primitive */
        std::shared_ptr<IMaterial> material; /**< Material of the hit surface */
    };

    /**
     * @brief Interface for all renderable objects in the raytracer.
     * 
     * Every object (Sphere, Plane, etc.) must implement this interface to be
     * handled by the core engine.
     */
    class IPrimitive {
    public:
        virtual ~IPrimitive() = default;

        /**
         * @brief Configure the primitive using a libconfig node.
         * @param node The configuration section for this primitive.
         */
        virtual void applyConfig(const libconfig::Setting &node) = 0;

        /**
         * @brief Check if a ray intersects this primitive.
         * 
         * @param ray The ray to check.
         * @param tMin The minimum distance along the ray.
         * @param tMax The maximum distance along the ray.
         * @param record Output structure to store hit information.
         * @return true if an intersection occurs within [tMin, tMax].
         */
        virtual bool hits(const Ray &ray, double tMin, double tMax, HitRecord &record) const = 0;

        /** @return The material associated with this primitive. */
        virtual std::shared_ptr<IMaterial> getMaterial() const = 0;

        /** @param material The new material to assign to this primitive. */
        virtual void setMaterial(std::shared_ptr<IMaterial> material) = 0;

        /** @return The transformation associated with this primitive. */
        virtual std::shared_ptr<ITransformation> getTransform() const = 0;

        /** @param transform The new transformation to assign to this primitive. */
        virtual void setTransform(std::shared_ptr<ITransformation> transform) = 0;

        /** @return The string type name of the primitive (e.g., "sphere"). */
        virtual std::string getTypeName() const = 0;
    };

}

#endif /* IOBJECT_HPP */
