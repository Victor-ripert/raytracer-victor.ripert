/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracer
*/

#include "Core/Render/Color.hpp"

namespace RayTracer {
    Color::Color() {
        r = 0;
        g = 0;
        b = 0;
    }

    Color::Color(size_t r, size_t g, size_t b) : r(r), g(g), b(b) {};

    std::string Color::to_str() const {
        return std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b);
    }

    void Color::setShade(double coefficent) {
        r = static_cast<size_t>(static_cast<double>(r) * coefficent);
        g = static_cast<size_t>(static_cast<double>(g) * coefficent);
        b = static_cast<size_t>(static_cast<double>(b) * coefficent);
    }
}