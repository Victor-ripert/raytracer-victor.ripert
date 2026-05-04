/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer-4
** File description:
** IError.hpp
*/

#ifndef RAYTRACER_IERROR_HPP
#define RAYTRACER_IERROR_HPP

#include <exception>

namespace RayTracer {
    typedef enum error_severity_e {
        ERROR_SEVERITY_MINOR = 0,
        ERROR_SEVERITY_LOW,
        ERROR_SEVERITY_MODERATE,
        ERROR_SEVERITY_CRITICAL,
        ERROR_SEVERITY_FATAL
    } error_severity_e;

    class IError : public std::exception {
    public:
        ~IError() override = default;

        virtual error_severity_e getSeverity() const noexcept = 0;
        const char *what() const noexcept override = 0;
    };
}

#endif // RAYTRACER_IERROR_HPP
