/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** raytracing_bootstrap
*/


#include "include/Vector3D.hpp"
#include "include/Point3D.hpp"
#include "include/objects/Sphere.hpp"
#include "include/Rectangle3D.hpp"
#include "include/Camera.hpp"
#include "include/Plain.hpp"
#include "include/Scene.hpp"
#include "include/Color.hpp"
#include "include/AmbientLight.hpp"

int main() {
    const std::size_t width = 800;
    const std::size_t height = 600;

    std::cout << "P3\n" << width << ' ' << height << "\n255" << std::endl;
    RayTracer::Camera cam;
    RayTracer::Scene scene;
    RayTracer::AmbientLight light(math::Point3D(1, 0, 0));
    scene.add_light(light);
    // RayTracer::Plain p(math::Point3D(10, 10, -5), math::Vector3D(0, 1, 1));
    // RayTracer::Sphere s(math::Point3D(0, 0, -10), 5, RayTracer::Color(255, 0, 255)); // Rose
    RayTracer::Sphere s2(math::Point3D(1.5, 0, -2), 0.5, RayTracer::Color(0, 0, 255)); // Bleu
    // RayTracer::Sphere s3(math::Point3D(-4, -4, -12.5), 5, RayTracer::Color(245, 73, 39)); // Saumon
    RayTracer::Sphere s4(math::Point3D(0, 59, -15), 60, RayTracer::Color(2, 99, 8)); // Vert (sol)
    // RayTracer::Sphere s(math::Point3D(0, 0, -2), 1, RayTracer::Color(255, 0, 255)); // Rose
    // RayTracer::Sphere s2(math::Point3D(0, 0, -1), 0.2, RayTracer::Color(0, 0, 255)); // Bleu
    // RayTracer::Sphere s3(math::Point3D(0, 0, 0), 0.5, RayTracer::Color(245, 73, 39)); // Saumon
    // RayTracer::Sphere s4(math::Point3D(0, 0, 0), 0.5, RayTracer::Color(2, 99, 8)); // Vert (sol)
    // std::cerr << "Distance between s and cam: " << s.get_center().distance_point(cam.origin) << std::endl;
    // std::cerr << "Distance between s2 and cam: " << s2.get_center().distance_point(cam.origin) << std::endl;
    // std::cerr << "Distance between s3 and cam: " << s3.get_center().distance_point(cam.origin) << std::endl;
    // scene.add_obj(&s);
    scene.add_obj(&s2);
    // scene.add_obj(&s3);
    scene.add_obj(&s4);
    for (std::size_t y = 0; y < height; y++) {
        for (std::size_t x = 0; x < width; x++) {
            double u = static_cast<double>(x) / static_cast<double>(width - 1);
            double v = static_cast<double>(y) / static_cast<double>(height - 1);
            RayTracer::Ray r = cam.ray(u, v);
            scene.hit_object(r);
        }
    }
}