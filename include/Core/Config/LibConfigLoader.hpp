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

    /**
     * @brief Wrapper around libconfig::Config for loading and accessing scene files.
     */
    class LibConfigLoader {
        public:
            LibConfigLoader() = default;
            ~LibConfigLoader() = default;

            /**
             * @brief Load a configuration file from the disk.
             * @param path Path to the .cfg file.
             * @throw ErrorConfig if the file is invalid or missing.
             */
            void load(const std::string &path);

            /** @return The root settings node of the loaded configuration. */
            libconfig::Setting &getRoot();
            /** @return The root settings node (const version). */
            const libconfig::Setting &getRoot() const;

        private:
            libconfig::Config _config; /**< The underlying libconfig object */
    };

}

#endif /* RAYTRACER_LIBCONFIGLOADER_HPP */
