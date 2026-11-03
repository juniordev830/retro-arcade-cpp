#ifndef RETRO_ARCADE_CORE_HPP
#define RETRO_ARCADE_CORE_HPP

#include <cmath>
#include <stdexcept>
#include <string>
#include <utility>

struct Vector2 {
    float x;
    float y;

    Vector2(float x = 0.0F, float y = 0.0F) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    float magnitude() const {
        return std::hypot(x, y);
    }

    Vector2 normalized() const {
        const float length = magnitude();
        if (length == 0.0F) return Vector2();
        return Vector2(x / length, y / length);
    }

    float distanceTo(const Vector2& other) const {
        return (*this - other).magnitude();
    }
};

class Entity {
public:
    std::string name;
    Vector2 position;
    Vector2 velocity;

    Entity(std::string name, float x, float y)
        : name(std::move(name)), position(x, y), velocity(0.0F, 0.0F) {}

    void update(float deltaTime) {
        if (!std::isfinite(deltaTime) || deltaTime < 0.0F) {
            throw std::invalid_argument("deltaTime must be finite and non-negative");
        }
        if (!std::isfinite(position.x) || !std::isfinite(position.y) ||
            !std::isfinite(velocity.x) || !std::isfinite(velocity.y)) {
            throw std::invalid_argument("position and velocity must be finite");
        }

        const Vector2 nextPosition = position + Vector2(
            velocity.x * deltaTime, velocity.y * deltaTime);
        if (!std::isfinite(nextPosition.x) || !std::isfinite(nextPosition.y)) {
            throw std::overflow_error("entity position overflowed");
        }
        position = nextPosition;
    }
};

#endif
