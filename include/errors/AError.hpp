/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer-4
** File description:
** AError.hpp
*/

#ifndef RAYTRACER_AERROR_HPP
#define RAYTRACER_AERROR_HPP

#include "errors/IError.hpp"
#include <string>
#include <utility>

namespace RayTracer {
    class AError : public IError {
        std::string full_err_msg;
        error_severity_e _severity;

    protected:
        explicit AError(std::string type_prefix, std::string detail, error_severity_e severity)
            : full_err_msg(std::move(type_prefix) + std::move(detail)), _severity(severity) {}

    public:
        error_severity_e getSeverity() const noexcept override { return _severity; }
        const char *what() const noexcept override { return full_err_msg.c_str(); }
    };
}

#endif // RAYTRACER_AERROR_HPP
