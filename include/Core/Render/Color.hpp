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
    /**
     * @brief Simple RGB color representation.
     */
    class Color {
        public:
            size_t r; /**< Red component [0, 255] */
            size_t g; /**< Green component [0, 255] */
            size_t b; /**< Blue component [0, 255] */

        /** @brief Default constructor (Black). */
        Color();
        /** @brief Constructor with RGB components. */
        Color(size_t r, size_t g, size_t b);
        /** @return String representation for PPM output ("R G B"). */
        std::string to_str() const;
        /** @brief Apply a shading coefficient to the color. */
        void setShade(double coefficient);
    };
}

#endif /* COLOR_HPP */