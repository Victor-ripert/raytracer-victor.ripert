/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer
** File description:
** LibConfigLoader
*/

#include <string>
#include "Core/Config/LibConfigLoader.hpp"
#include "errors/RayTracerErrors.hpp"

namespace RayTracer {

    void LibConfigLoader::load(const std::string &path)
    {
        try {
            _config.readFile(path.c_str());
        } catch (const libconfig::FileIOException &) {
            throw ErrorConfig(std::string("I/O error reading config: ") + path);
        } catch (const libconfig::ParseException &pex) {
            throw ErrorConfig(
                std::string("Parse error ") + pex.getFile() + ":" + std::to_string(pex.getLine()) + " — " + pex.getError());
        }
    }

    libconfig::Setting &LibConfigLoader::getRoot()
    {
        return _config.getRoot();
    }

    const libconfig::Setting &LibConfigLoader::getRoot() const
    {
        return _config.getRoot();
    }

}
