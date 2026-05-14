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

    void Color::clampColor() {
        r = r > 255 ? 255 : r;
        g = g > 255 ? 255 : g;
        b = b > 255 ? 255 : b;
    }

    Color Color::operator+(const Color color) const {
        return Color(r + color.r, g + color.g, b + color.b);
    }

    void Color::operator+=(const Color color) {
        r += color.r;
        g += color.g;
        b += color.b;
    }

    Color Color::operator/(const Color color) const {
        return Color(r / color.r, g / color.g, b / color.b);
    }

    void Color::operator/=(const Color color) {
        r /= color.r;
        g /= color.g;
        b /= color.b;
    }

    Color Color::operator/(const int nb) const {
        return Color(r / nb, g / nb, b / nb);
    }

    void Color::operator/=(const int nb) {
        r /= nb;
        g /= nb;
        b /= nb;
    }
}