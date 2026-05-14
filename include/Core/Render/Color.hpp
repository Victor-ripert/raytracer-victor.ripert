/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracer
*/


#ifndef COLOR_HPP
    #define COLOR_HPP
    #include "Math/Ray.hpp"

namespace RayTracer {
    class Color {
        public:
            size_t r;
            size_t g;
            size_t b;

        Color();
        Color(size_t r, size_t g, size_t b);
        std::string to_str();
        void setShade(double coefficient);
        void clampColor();
        Color operator+(const Color color) const;
        void operator+=(const Color color);
        Color operator/(const Color color) const;
        void operator/=(const Color color);
        Color operator/(const int nb) const;
        void operator/=(const int nb);
    };
}

#endif /* COLOR_HPP */