/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** PluginLoader.hpp
*/

#ifndef PLUGINLOADER_HPP
#define PLUGINLOADER_HPP

#include <string>
#include <dlfcn.h>
#include <memory>
#include <stdexcept>
#include <iostream>

namespace RayTracer {

    /**
     * @brief A utility class to load dynamic libraries (.so) and instantiate objects.
     */
    class PluginLoader {
    public:
        PluginLoader() = default;
        ~PluginLoader() = default;

        /**
         * @brief Loads a plugin and returns an instance of the requested type.
         * 
         * @tparam T The interface type (e.g., IPrimitive, ILight).
         * @param path Path to the .so file.
         * @param entryPoint The name of the C-style factory function (e.g., "create_primitive").
         * @return std::shared_ptr<T> A managed pointer to the new instance.
         */
        template <typename T>
        static std::shared_ptr<T> load(const std::string &path, const std::string &entryPoint) {
            void *handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!handle) {
                throw std::runtime_error("PluginLoader: Failed to load " + path + ": " + dlerror());
            }

            // Reset errors
            dlerror();

            // Function pointer type for the factory
            typedef T* (*FactoryFunction)();
            
            FactoryFunction factory = reinterpret_cast<FactoryFunction>(dlsym(handle, entryPoint.c_str()));
            
            const char *error = dlerror();
            if (error) {
                dlclose(handle);
                throw std::runtime_error("PluginLoader: Failed to find symbol " + entryPoint + " in " + path + ": " + error);
            }

            // Create the instance
            T *instance = factory();
            if (!instance) {
                dlclose(handle);
                throw std::runtime_error("PluginLoader: Factory returned null in " + path);
            }

            // Return shared_ptr with a custom deleter that also closes the library handle
            return std::shared_ptr<T>(instance, [handle](T *ptr) {
                delete ptr;
                dlclose(handle);
            });
        }
    };
}

#endif /* PLUGINLOADER_HPP */
