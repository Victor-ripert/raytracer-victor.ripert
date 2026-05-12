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

        if (!root.exists("camera"))
            throw ErrorConfig("missing required group \"camera\"");
        const libconfig::Setting &cameraGroup = root["camera"];

        ConfigParse::readRenderResolution(cameraGroup, params.width, params.height);
        ConfigParse::applyCameraFromConfig(cameraGroup, camera);
        camera.setImageDimensions(params.width, params.height);
        camera.rebuildViewPlane();

        if (auto primitiveListOpt = ConfigParse::optionalList(root, "primitives", "\"primitives\" must be a list")) {
            const libconfig::Setting &primitiveList = primitiveListOpt->get();
            PrimitiveFactory primitiveFactory(pluginDir);
            const int primitiveCount = primitiveList.getLength();
            for (int primitiveIndex = 0; primitiveIndex < primitiveCount; ++primitiveIndex) {
                const libconfig::Setting &primitiveNode = primitiveList[primitiveIndex];
                const std::string primitiveType = ConfigParse::readType(primitiveNode, "primitives[]");
                const PrimitiveConfig primitiveConfig = ConfigParse::readPrimitiveConfig(primitiveType, primitiveNode);
                scene.add_obj(primitiveFactory.create(primitiveType, primitiveConfig));
            }
        }

        if (auto lightListOpt = ConfigParse::optionalList(root, "lights", "\"lights\" must be a list")) {
            const libconfig::Setting &lightList = lightListOpt->get();
            LightFactory lightFactory;
            const int lightCount = lightList.getLength();
            for (int lightIndex = 0; lightIndex < lightCount; lightIndex++) {
                const libconfig::Setting &lightNode = lightList[lightIndex];
                const std::string lightType = ConfigParse::readType(lightNode, "lights[]");
                scene.add_light(lightFactory.create(lightType, lightNode));
            }
        }
    }

}
