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

    std::string Color::to_str() {
        return std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b);
    }

    void Color::setShade(double coefficent) {
        if (coefficent == 0)
            return;
        r = r * coefficent;
        g = g * coefficent;
        b = b * coefficent;
        r = r > 255 ? 255 : r;
        g = g > 255 ? 255 : g;
        b = b > 255 ? 255 : b;
    }
}