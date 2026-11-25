#ifndef RETRO_ARCADE_COLLISION_HPP
#define RETRO_ARCADE_COLLISION_HPP

#include "core.hpp"

#include <algorithm>
#include <optional>
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

// Earliest contact in [0,1] while moving a box by displacement against
// a stationary box. Returning nullopt means no contact during the step.
inline std::optional<double> sweptContact(const AABB2& moving, const Vector2& displacement,
                                          const AABB2& target) {
    if (!std::isfinite(displacement.x) || !std::isfinite(displacement.y)) {
        throw std::invalid_argument("displacement must be finite");
    }
    // AABB members are public; revalidate before using a possibly mutated box.
    const AABB2 a(moving.center, moving.halfExtents);
    const AABB2 b(target.center, target.halfExtents);
    if (a.intersects(b)) return 0.0;

    double entry = 0.0;
    double exit = 1.0;
    auto axis = [&](double start, double destination, double reach, double delta) {
        const double relative = start - destination;
        if (delta == 0.0) return std::abs(relative) <= reach;
        double first = (-reach - relative) / delta;
        double last = (reach - relative) / delta;
        if (first > last) std::swap(first, last);
        entry = std::max(entry, first);
        exit = std::min(exit, last);
        return entry <= exit;
    };
    if (!axis(a.center.x, b.center.x,
              static_cast<double>(a.halfExtents.x) + b.halfExtents.x, displacement.x) ||
        !axis(a.center.y, b.center.y,
              static_cast<double>(a.halfExtents.y) + b.halfExtents.y, displacement.y))
        return std::nullopt;
    return entry;
}

#endif
