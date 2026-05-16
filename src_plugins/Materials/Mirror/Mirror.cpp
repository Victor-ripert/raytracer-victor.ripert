/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** Mirror material plugin
*/

#include "Mirror.hpp"

extern "C" RayTracer::IMaterial* create_material()
{
    return new RayTracer::Mirror();
}

extern "C" void destroy_material(RayTracer::IMaterial* material)
{
    delete material;
}

extern "C" const char* get_type()
{
    return "mirror";
}
