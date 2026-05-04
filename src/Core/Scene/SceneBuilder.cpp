/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** SceneBuilder
*/

#include "Core/Scene/SceneBuilder.hpp"
#include "Core/Config/LibConfigLoader.hpp"
#include "Core/Factory/PrimitiveFactory.hpp"
#include "Core/Lights/LightFactory.hpp"
#include "Core/Config/ConfigParse.hpp"
#include "errors/RayTracerErrors.hpp"

namespace RayTracer {

    void SceneBuilder::build(const std::string &scenePath, Scene &scene, Camera &camera, RenderParams &params)
    {
        LibConfigLoader loader;
        loader.load(scenePath);
        const libconfig::Setting &root = loader.getRoot();

        std::string pluginDir = "plugins";
        root.lookupValue("plugin_dir", pluginDir);

        if (!root.exists("camera")) {
            throw ErrorConfig("missing required group \"camera\"");
        }
        const libconfig::Setting &cameraGroup = root["camera"];
        if (!cameraGroup.exists("resolution")) {
            throw ErrorConfig("camera: missing \"resolution\" group");
        }
        const libconfig::Setting &resolution = cameraGroup["resolution"];
        int imageWidth = 0;
        int imageHeight = 0;
        if (!resolution.lookupValue("width", imageWidth) || !resolution.lookupValue("height", imageHeight)) {
            throw ErrorConfig("camera.resolution: width and height are required");
        }
        if (imageWidth <= 0 || imageHeight <= 0) {
            throw ErrorConfig("camera.resolution: width and height must be positive");
        }
        params.width = static_cast<unsigned int>(imageWidth);
        params.height = static_cast<unsigned int>(imageHeight);

        if (cameraGroup.exists("position")) {
            camera.origin = ConfigParse::readPoint3(cameraGroup["position"], "camera.position");
        } else if (cameraGroup.exists("origin")) {
            camera.origin = ConfigParse::readPoint3(cameraGroup["origin"], "camera.origin");
        }

        double verticalFov = 72.0;
        double fovDouble = 0;
        int fovInt = 0;
        if (cameraGroup.lookupValue("fieldOfView", fovDouble)) {
            verticalFov = fovDouble;
        } else if (cameraGroup.lookupValue("fov", fovDouble)) {
            verticalFov = fovDouble;
        } else if (cameraGroup.lookupValue("fieldOfView", fovInt)) {
            verticalFov = static_cast<double>(fovInt);
        } else if (cameraGroup.lookupValue("fov", fovInt)) {
            verticalFov = static_cast<double>(fovInt);
        }
        camera.setVerticalFovDegrees(verticalFov);

        if (cameraGroup.exists("rotation")) {
            camera.setRotationDegrees(ConfigParse::readVector3(cameraGroup["rotation"], "camera.rotation"));
        } else {
            camera.setRotationDegrees(math::Vector3D(0, 0, 0));
        }

        camera.setImageDimensions(params.width, params.height);
        camera.rebuildViewPlane();

        if (root.exists("primitives")) {
            const libconfig::Setting &primitiveList = root["primitives"];
            if (primitiveList.getType() != libconfig::Setting::TypeList) {
                throw ErrorConfig("\"primitives\" must be a list");
            }
            PrimitiveFactory primitiveFactory(pluginDir);
            const int primitiveCount = primitiveList.getLength();
            for (int primitiveIndex = 0; primitiveIndex < primitiveCount; ++primitiveIndex) {
                const libconfig::Setting &primitiveNode = primitiveList[primitiveIndex];
                const std::string primitiveType = ConfigParse::readType(primitiveNode, "primitives[]");
                scene.add_obj(primitiveFactory.create(primitiveType, primitiveNode));
            }
        }

        if (root.exists("lights")) {
            const libconfig::Setting &lightList = root["lights"];
            if (lightList.getType() != libconfig::Setting::TypeList) {
                throw ErrorConfig("\"lights\" must be a list");
            }
            LightFactory lightFactory;
            const int lightCount = lightList.getLength();
            if (lightCount > 0) {
                const libconfig::Setting &lightNode = lightList[0];
                const std::string lightType = ConfigParse::readType(lightNode, "lights[]");
                scene.add_light(lightFactory.create(lightType, lightNode));
            }
        }
    }

}
