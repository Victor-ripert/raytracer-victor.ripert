/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** raytracing_bootstrap
*/

#include <memory>
#include <iostream>
#include "include/Math/Vector3D.hpp"
#include "include/Math/Point3D.hpp"
#include "include/Core/PluginLoader.hpp"
#include "include/Core/Camera.hpp"
#include "include/Core/Scene.hpp"
#include "include/Core/Color.hpp"
#include "include/Core/PointLight.hpp"
#include "include/API/IPrimitive.hpp"

int main() {
    const std::size_t width = 800;
    const std::size_t height = 600;

    std::cout << "P3\n" << width << ' ' << height << "\n255" << std::endl;
    RayTracer::Camera cam;
    RayTracer::Scene scene;
    
    // Create light as a shared_ptr
    auto light = std::make_shared<RayTracer::PointLight>(math::Point3D(1, 0, 0));
    scene.add_light(light);

    try {
        // Demonstrate Plugin Loading
        // Note: These paths assume the plugins are compiled into the ./plugins/ directory
        auto s2 = RayTracer::PluginLoader::load<RayTracer::IPrimitive>("./plugins/sphere.so", "create_primitive");
        auto s4 = RayTracer::PluginLoader::load<RayTracer::IPrimitive>("./plugins/sphere.so", "create_primitive");
        // For now, since they are default initialized, we'd need setters or a config system to move them
        // But this proves the DLOpen logic works!
        
        scene.add_obj(s2);
        scene.add_obj(s4);
    } catch (const std::exception &e) {
        std::cerr << "Error loading plugins: " << e.what() << std::endl;
        // Fallback or exit
        return 84;
    }

    for (std::size_t y = 0; y < height; y++) {
        for (std::size_t x = 0; x < width; x++) {
            double u = static_cast<double>(x) / static_cast<double>(width - 1);
            double v = static_cast<double>(y) / static_cast<double>(height - 1);
            RayTracer::Ray r = cam.ray(u, v);
            scene.hit_object(r);
        }
    }
    return 0;
}
