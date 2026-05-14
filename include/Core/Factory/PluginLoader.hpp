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
#include <iostream>
#include "errors/RayTracerErrors.hpp"

namespace RayTracer {

    /**
     * @brief A structure to hold the library handle and factory symbols.
     * 
     * @tparam T The interface type (e.g., IPrimitive, ILight).
     */
    template <typename T>
    struct PluginSymbols {
        std::shared_ptr<void> handle;
        T* (*create)();
        void (*destroy)(T*);
        const char* (*getType)();
    };

    /**
     * @brief A utility class to load dynamic libraries (.so) and retrieve symbols.
     */
    class PluginLoader {
    public:
        PluginLoader() = default;
        ~PluginLoader() = default;

        /**
         * @brief Loads a plugin and returns its creation/destruction symbols.
         * 
         * @tparam T The interface type.
         * @param path Path to the .so file.
         * @param createName The name of the creation symbol.
         * @param destroyName The name of the destruction symbol.
         * @param typeName The name of the type identification symbol.
         * @return PluginSymbols<T> The package of symbols.
         */
        template <typename T>
        static PluginSymbols<T> load(const std::string &path, const std::string &createName, const std::string &destroyName, const std::string &typeName) {
            void *rawHandle = dlopen(path.c_str(), RTLD_LAZY);
            if (!rawHandle) {
                const char *load_error = dlerror();
                throw ErrorPlugin(
                    std::string("PluginLoader: Failed to load ") + path + ": "
                    + (load_error ? load_error : "unknown error"));
            }

            // Create a shared_ptr for the handle with dlclose as deleter
            std::shared_ptr<void> handle(rawHandle, dlclose);

            dlerror(); // Reset errors

            auto create = reinterpret_cast<T* (*)()>(dlsym(rawHandle, createName.c_str()));
            const char *createError = dlerror();
            if (createError) {
                throw ErrorPlugin(std::string("PluginLoader: Failed to find symbol ") + createName + ": " + createError);
            }

            auto destroy = reinterpret_cast<void (*)(T*)>(dlsym(rawHandle, destroyName.c_str()));
            const char *destroyError = dlerror();
            if (destroyError) {
                throw ErrorPlugin(std::string("PluginLoader: Failed to find symbol ") + destroyName + ": " + destroyError);
            }

            auto getType = reinterpret_cast<const char* (*)()>(dlsym(rawHandle, typeName.c_str()));
            const char *getTypeError = dlerror();
            if (getTypeError) {
                throw ErrorPlugin(std::string("PluginLoader: Failed to find symbol ") + typeName + ": " + getTypeError);
            }

            return {handle, create, destroy, getType};
        }
    };
}

#endif /* PLUGINLOADER_HPP */
