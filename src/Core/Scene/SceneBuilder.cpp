/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** SceneBuilder
*/

#include <iostream>
#include "Core/Scene/SceneBuilder.hpp"
#include "Core/Config/LibConfigLoader.hpp"
#include "Core/Factory/PrimitiveFactory.hpp"
#include "Core/Lights/LightFactory.hpp"
#include "Core/Lights/DirectionalLight.hpp"
#include "Core/Config/ConfigParse.hpp"
#include "Core/Materials/DefaultMaterial.hpp"
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
                std::shared_ptr<IPrimitive> primitive = primitiveFactory.create(primitiveType, primitiveConfig);
                try {
                    if (!primitive->getMaterial())
                        throw ErrorConfig("primitive \"" + primitiveType + "\": no material specified, assigning default",  ERROR_SEVERITY_LOW);
                } catch (const ErrorConfig &materialError) {
                    std::cerr << materialError.what() << '\n';
                    primitive->setMaterial(std::make_shared<DefaultMaterial>(primitiveConfig.color));
                }
                scene.add_obj(primitive);
            }
        }

        if (auto lightListOpt = ConfigParse::optionalList(root, "lights", "\"lights\" must be a list")) {
            const libconfig::Setting &lightList = lightListOpt->get();
            LightFactory lightFactory;
            const int lightCount = lightList.getLength();
            if (lightCount > 0) {
                const libconfig::Setting &lightNode = lightList[0];
                const std::string lightType = ConfigParse::readType(lightNode, "lights[]");
                scene.add_light(lightFactory.create(lightType, lightNode));
            }
        }

        try {
            if (!scene.light)
                throw ErrorConfig("no light specified, assigning default directional light", ERROR_SEVERITY_LOW);
        } catch (const ErrorConfig &lightError) {
            std::cerr << lightError.what() << '\n';
            scene.add_light(std::make_shared<DirectionalLight>(math::Vector3D(0, 1, 0)));
        }
    }

}
