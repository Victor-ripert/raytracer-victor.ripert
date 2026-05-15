/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** Silver material plugin
*/

#include "Silver.hpp"

extern "C" RayTracer::IMaterial* create_material()
{
    return new RayTracer::Silver();
}

extern "C" void destroy_material(RayTracer::IMaterial* material)
{
    delete material;
}

extern "C" const char* get_type()
{
    return "silver";
}
