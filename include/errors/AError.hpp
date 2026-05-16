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
    /**
     * @brief Abstract base class for Raytracer exceptions.
     */
    class AError : public IError {
        std::string full_err_msg; /**< The full concatenated error message */
        error_severity_e _severity; /**< The severity level of the error */

    protected:
        /**
         * @brief Construct a new AError.
         * @param type_prefix Prefix indicating the error source (Core, Plugin, etc.).
         * @param detail Specific details about the failure.
         * @param severity Importance of the error.
         */
        explicit AError(std::string type_prefix, std::string detail, error_severity_e severity)
            : full_err_msg(std::move(type_prefix) + std::move(detail)), _severity(severity) {}

    public:
        /** @return The severity level of the exception. */
        error_severity_e getSeverity() const noexcept override { return _severity; }
        /** @return The full C-style error message. */
        const char *what() const noexcept override { return full_err_msg.c_str(); }
    };
}

#endif // RAYTRACER_AERROR_HPP
