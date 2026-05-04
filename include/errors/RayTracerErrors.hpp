/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer-4
** File description:
** RayTracerErrors.hpp
*/

#ifndef RAYTRACER_RAYTRACERERRORS_HPP
#define RAYTRACER_RAYTRACERERRORS_HPP

#include "errors/AError.hpp"
#include <string>
#include <utility>

namespace RayTracer {
    class ErrorCore : public AError {
    public:
        explicit ErrorCore(std::string message, error_severity_e severity = ERROR_SEVERITY_FATAL)
            : AError("Type: Core\nMessage: ", std::move(message), severity) {}
    };

    class ErrorPlugin : public AError {
    public:
        explicit ErrorPlugin(std::string message, error_severity_e severity = ERROR_SEVERITY_CRITICAL)
            : AError("Type: Plugin\nMessage: ", std::move(message), severity) {}
    };
}

#endif // RAYTRACER_RAYTRACERERRORS_HPP
