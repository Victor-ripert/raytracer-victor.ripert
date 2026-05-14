/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** LightFactory
*/

#include "Core/Lights/LightFactory.hpp"
#include "Core/Config/ConfigParse.hpp"
#include "Core/Lights/DirectionalLight.hpp"
#include "Core/Lights/PointLight.hpp"
#include "errors/RayTracerErrors.hpp"

namespace RayTracer {

    std::shared_ptr<ILight> LightFactory::create(const std::string &typeName, const libconfig::Setting &node) const
    {
        const std::string kind = ConfigParse::toLower(typeName);

        if (kind == "point") {
            const math::Point3D position = ConfigParse::readPoint3(node["position"], "point.position");
            return std::make_shared<PointLight>(position);
        }

        if (kind == "directional") {
            const math::Point3D position = ConfigParse::readPoint3(node["position"], "directional.position");
            const math::Vector3D directionTowardLight = ConfigParse::readVector3(node["direction"], "directional.direction");
            // const double lightning_angle =    ----> rajouter l'angle deppuis le fichuer de config
            return std::make_shared<DirectionalLight>(position, directionTowardLight, 45.0);
        }

        throw ErrorConfig(std::string("Unknown light type: ") + typeName);
    }

}
