/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** TintedMirror material plugin
*/

#include "TintedMirror.hpp"

extern "C" RayTracer::IMaterial* create_material()
{
    return new RayTracer::TintedMirror();
}

extern "C" void destroy_material(RayTracer::IMaterial* material)
{
    delete material;
}

extern "C" const char* get_type()
{
    return "tinted_mirror";
}
