/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** RayTracing
*/

#include <cmath>
#include <numbers>
#include "Core/Render/Camera.hpp"
#include "Core/Config/ConfigUtils.hpp"

namespace RayTracer {

    namespace {

        math::Vector3D cross3(const math::Vector3D &a, const math::Vector3D &b)
        {
            return math::Vector3D(
                a._y * b._z - a._z * b._y,
                a._z * b._x - a._x * b._z,
                a._x * b._y - a._y * b._x);
        }

        math::Vector3D rotateAroundX(math::Vector3D vector, double radians)
        {
            const double cosine = std::cos(radians);
            const double sine = std::sin(radians);
            return math::Vector3D(vector._x, vector._y * cosine - vector._z * sine, vector._y * sine + vector._z * cosine);
        }

        math::Vector3D rotateAroundY(math::Vector3D vector, double radians)
        {
            const double cosine = std::cos(radians);
            const double sine = std::sin(radians);
            return math::Vector3D(vector._x * cosine + vector._z * sine, vector._y, -vector._x * sine + vector._z * cosine);
        }

        math::Vector3D rotateAroundZ(math::Vector3D vector, double radians)
        {
            const double cosine = std::cos(radians);
            const double sine = std::sin(radians);
            return math::Vector3D(vector._x * cosine - vector._y * sine, vector._x * sine + vector._y * cosine, vector._z);
        }

        double lengthSquared(const math::Vector3D &vector)
        {
            return vector._x * vector._x + vector._y * vector._y + vector._z * vector._z;
        }

    }

    Camera::Camera()
    {
        origin = math::Point3D();
        screen = Rectangle3D();
    }

    void Camera::applyConfig(const libconfig::Setting &node)
    {
        if (node.exists("position"))
            origin = ConfigUtils::readPoint3(node["position"]);
        else if (node.exists("origin"))
            origin = ConfigUtils::readPoint3(node["origin"]);

        double verticalFov = 72.0;
        if (ConfigUtils::tryReadDouble(node, "fieldOfView", verticalFov))
            _verticalFovDegrees = verticalFov;
        else if (ConfigUtils::tryReadDouble(node, "fov", verticalFov))
            _verticalFovDegrees = verticalFov;

        if (node.exists("rotation"))
            _rotationDegrees = ConfigUtils::readVector3(node["rotation"]);
        else
            _rotationDegrees = math::Vector3D(0, 0, 0);
    }

    void Camera::setImageDimensions(unsigned int width, unsigned int height)
    {
        _imageWidth = width;
        _imageHeight = height;
    }

    void Camera::setVerticalFovDegrees(double degrees)
    {
        _verticalFovDegrees = degrees;
    }

    void Camera::setRotationDegrees(const math::Vector3D &eulerDegrees)
    {
        _rotationDegrees = eulerDegrees;
    }

    void Camera::rebuildViewPlane()
    {
        if (_imageWidth == 0 || _imageHeight == 0) {
            return;
        }

        const double focal = 1.0;
        const double aspect = static_cast<double>(_imageWidth) / static_cast<double>(_imageHeight);
        const double verticalFovRadians = _verticalFovDegrees * std::numbers::pi / 180.0;
        const double halfHeight = std::tan(verticalFovRadians * 0.5) * focal;
        const double halfWidth = halfHeight * aspect;

        const double radiansX = _rotationDegrees._x * std::numbers::pi / 180.0;
        const double radiansY = _rotationDegrees._y * std::numbers::pi / 180.0;
        const double radiansZ = _rotationDegrees._z * std::numbers::pi / 180.0;

        math::Vector3D forward(0, 0, -1);
        forward = rotateAroundX(forward, radiansX);
        forward = rotateAroundY(forward, radiansY);
        forward = rotateAroundZ(forward, radiansZ);
        forward.normalize();

        const math::Vector3D worldUp(0, 1, 0);
        math::Vector3D right = cross3(forward, worldUp);
        if (lengthSquared(right) < 1e-24) {
            right = math::Vector3D(1, 0, 0);
        } else {
            right.normalize();
        }
        math::Vector3D up = cross3(right, forward);
        up.normalize();

        const math::Point3D center = origin + forward * focal;
        const math::Point3D screenOrigin = center - right * halfWidth + up * halfHeight;
        screen.origin = screenOrigin;
        screen.bottom_side = right * (2 * halfWidth);
        screen.left_side = up * (-2 * halfHeight);
    }

    Ray Camera::ray(double u, double v)
    {
        math::Point3D pixel = screen.pointAt(u, v);
        math::Vector3D direction = pixel - origin;
        return Ray(origin, direction);
    }
}
