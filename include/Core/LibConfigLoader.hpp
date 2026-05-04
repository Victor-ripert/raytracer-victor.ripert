/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** LibConfigLoader
*/

#ifndef RAYTRACER_LIBCONFIGLOADER_HPP
#define RAYTRACER_LIBCONFIGLOADER_HPP

#include <libconfig.h++>
#include <string>

namespace RayTracer {

    class LibConfigLoader {
        public:
            LibConfigLoader() = default;
            ~LibConfigLoader() = default;

            void load(const std::string &path);

            libconfig::Setting &getRoot();
            const libconfig::Setting &getRoot() const;

        private:
            libconfig::Config _config;
    };

}

#endif /* RAYTRACER_LIBCONFIGLOADER_HPP */
