/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** SceneBuilder
*/

#include <iostream>
#include "Core/Scene/SceneBuilder.hpp"
#include "Core/Config/LibConfigLoader.hpp"
#include "Core/Config/ConfigUtils.hpp"
#include "Core/Factory/PrimitiveFactory.hpp"
#include "Core/Lights/LightFactory.hpp"
#include "Core/Lights/DirectionalLight.hpp"
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

        // Read resolution
        if (cameraGroup.exists("resolution")) {
            const libconfig::Setting &resolution = cameraGroup["resolution"];
            int w = 0, h = 0;
            if (resolution.lookupValue("width", w) && resolution.lookupValue("height", h)) {
                params.width = static_cast<unsigned int>(w);
                params.height = static_cast<unsigned int>(h);
            }
        }
        
        camera.applyConfig(cameraGroup);
        camera.setImageDimensions(params.width, params.height);
        camera.rebuildViewPlane();

        if (auto primitiveListOpt = ConfigUtils::optionalList(root, "primitives")) {
            const libconfig::Setting &primitiveList = primitiveListOpt->get();
            PrimitiveFactory primitiveFactory(pluginDir);
            const int primitiveCount = primitiveList.getLength();
            for (int primitiveIndex = 0; primitiveIndex < primitiveCount; ++primitiveIndex) {
                const libconfig::Setting &primitiveNode = primitiveList[primitiveIndex];
                std::string type;
                if (!primitiveNode.lookupValue("type", type))
                    continue;
                std::shared_ptr<IPrimitive> primitive = primitiveFactory.create(ConfigUtils::toLower(type), primitiveNode);
                if (!primitive->getMaterial()) {
                    primitive->setMaterial(std::make_shared<DefaultMaterial>(Color(128, 128, 128)));
                }
                scene.add_obj(primitive);
            }
        }

        if (auto lightListOpt = ConfigUtils::optionalList(root, "lights")) {
            const libconfig::Setting &lightList = lightListOpt->get();
            LightFactory lightFactory;
            const int lightCount = lightList.getLength();
            for (int lightIndex = 0; lightIndex < lightCount; ++lightIndex) {
                const libconfig::Setting &lightNode = lightList[lightIndex];
                std::string type;
                if (!lightNode.lookupValue("type", type))
                    continue;
                scene.add_light(lightFactory.create(ConfigUtils::toLower(type), lightNode));
            }
        }

        if (scene.getLights().empty()) {
            std::cerr << "no light specified, assigning default directional light\n";
            scene.add_light(std::make_shared<DirectionalLight>(math::Vector3D(0, 1, 0)));
        }
    }

}
