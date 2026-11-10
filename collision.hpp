#ifndef RETRO_ARCADE_COLLISION_HPP
#define RETRO_ARCADE_COLLISION_HPP

#include "core.hpp"

#include <cmath>
#include <stdexcept>

// Axis-aligned bounds described by a center point and half-extents.
struct AABB2 {
    Vector2 center;
    Vector2 halfExtents;

    AABB2(Vector2 center, Vector2 halfExtents)
        : center(center), halfExtents(halfExtents) {
        if (!std::isfinite(center.x) || !std::isfinite(center.y)) {
            throw std::invalid_argument("collision center must be finite");
        }
        if (!std::isfinite(halfExtents.x) || !std::isfinite(halfExtents.y) ||
            halfExtents.x < 0.0F || halfExtents.y < 0.0F) {
            throw std::invalid_argument(
                "collision half-extents must be finite and non-negative");
        }
    }

    // Touching edges count as contact.
    bool intersects(const AABB2& other) const noexcept {
        const double dx = std::abs(
            static_cast<double>(center.x) - static_cast<double>(other.center.x));
        const double dy = std::abs(
            static_cast<double>(center.y) - static_cast<double>(other.center.y));
        const double reachX = static_cast<double>(halfExtents.x) +
                              static_cast<double>(other.halfExtents.x);
        const double reachY = static_cast<double>(halfExtents.y) +
                              static_cast<double>(other.halfExtents.y);
        return dx <= reachX && dy <= reachY;
    }

    bool contains(const Vector2& point) const noexcept {
        const double dx = std::abs(
            static_cast<double>(center.x) - static_cast<double>(point.x));
        const double dy = std::abs(
            static_cast<double>(center.y) - static_cast<double>(point.y));
        return dx <= static_cast<double>(halfExtents.x) &&
               dy <= static_cast<double>(halfExtents.y);
    }
};

#endif
