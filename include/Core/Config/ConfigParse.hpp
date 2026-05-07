/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** ConfigParse — libconfig helpers
*/

#ifndef RAYTRACER_CONFIGPARSE_HPP
#define RAYTRACER_CONFIGPARSE_HPP

#include <functional>
#include <libconfig.h++>
#include <optional>
#include <string>
#include "API/PrimitiveConfig.hpp"
#include "Core/Render/Color.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

namespace RayTracer {

    class Camera;

    namespace ConfigParse {

        std::string toLower(std::string value);
        std::string readType(const libconfig::Setting &node, const char *contextLabel);
        PrimitiveConfig readPrimitiveConfig(const std::string &typeName, const libconfig::Setting &node);

        math::Point3D readPoint3(const libconfig::Setting &group, const char *contextLabel);
        math::Vector3D readVector3(const libconfig::Setting &group, const char *contextLabel);
        Color readRgbColor(const libconfig::Setting &group, const char *contextLabel);

        void readRenderResolution(const libconfig::Setting &cameraGroup, unsigned int &width, unsigned int &height);
        void applyCameraFromConfig(const libconfig::Setting &cameraGroup, Camera &camera);
        std::optional<std::reference_wrapper<const libconfig::Setting>> optionalList(const libconfig::Setting &root, const char *key, const char *notListError);

    }

}

#endif /* RAYTRACER_CONFIGPARSE_HPP */
