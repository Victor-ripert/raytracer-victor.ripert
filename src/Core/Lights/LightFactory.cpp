/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** LightFactory
*/

#include "Core/Lights/LightFactory.hpp"
#include "Core/Config/ConfigUtils.hpp"
#include "Core/Lights/DirectionalLight.hpp"
#include "Core/Lights/PointLight.hpp"
#include "errors/RayTracerErrors.hpp"

namespace RayTracer {

    std::shared_ptr<ILight> LightFactory::create(const std::string &typeName, const libconfig::Setting &node) const
    {
        const std::string kind = ConfigUtils::toLower(typeName);

        if (kind == "point") {
            const math::Point3D position = ConfigUtils::readPoint3(node["position"]);
            return std::make_shared<PointLight>(position);
        }

        if (kind == "directional") {
            const math::Vector3D directionTowardLight = ConfigUtils::readVector3(node["direction"]);
            return std::make_shared<DirectionalLight>(directionTowardLight);
        }

        throw ErrorConfig(std::string("Unknown light type: ") + typeName);
    }

}
