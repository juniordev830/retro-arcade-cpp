#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct Vector2 {
    float x;
    float y;

    Vector2(float x = 0, float y = 0) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }
};

class Entity {
public:
    std::string name;
    Vector2 position;
    Vector2 velocity;

    Entity(std::string name, float x, float y) : name(name), position(x, y), velocity(0, 0) {}

    void update(float deltaTime) {
        position = position + Vector2(velocity.x * deltaTime, velocity.y * deltaTime);
    }
};

int main() {
    std::cout << "🕹️ Retro Arcade C++ Engine core running..." << std::endl;
    Entity player("Ship", 100.0f, 100.0f);
    player.velocity = Vector2(50.0f, -20.0f);

    std::cout << "Initial Pos: (" << player.position.x << ", " << player.position.y << ")\n";
    player.update(0.16f);
    std::cout << "Updated Pos (0.16s dt): (" << player.position.x << ", " << player.position.y << ")\n";

    return 0;
}
