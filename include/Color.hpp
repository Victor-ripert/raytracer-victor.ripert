/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracer
*/


#ifndef COLOR_HPP
    #define COLOR_HPP
    #include "Ray.hpp"

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
    };
}

#endif /* COLOR_HPP */