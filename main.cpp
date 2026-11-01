#include <cmath>
#include <iostream>
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

    float magnitude() const {
        return std::hypot(x, y);
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

#ifndef RETRO_ARCADE_NO_MAIN
int main() {
    std::cout << "Retro Arcade C++ core running..." << std::endl;
    Entity player("Ship", 100.0F, 100.0F);
    player.velocity = Vector2(50.0F, -20.0F);

    std::cout << "Initial position: (" << player.position.x << ", "
              << player.position.y << ")\n";
    player.update(0.16F);
    std::cout << "Updated position (0.16s dt): (" << player.position.x
              << ", " << player.position.y << ")\n";
    return 0;
}
#endif
