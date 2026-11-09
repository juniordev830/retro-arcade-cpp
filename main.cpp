#include "collision.hpp"
#include <iostream>

#ifndef RETRO_ARCADE_NO_MAIN
int main() {
    std::cout << "Retro Arcade C++ core running..." << std::endl;
    Entity player("Ship", 100.0F, 100.0F);
    player.velocity = Vector2(50.0F, -20.0F);

    const AABB2 shipHitbox(player.position, Vector2(6.0F, 6.0F));
    const AABB2 asteroidHitbox(Vector2(109.0F, 104.0F), Vector2(4.0F, 4.0F));
    std::cout << "Ship overlaps asteroid: "
              << (shipHitbox.intersects(asteroidHitbox) ? "yes" : "no") << "\n";

    std::cout << "Initial position: (" << player.position.x << ", "
              << player.position.y << ")\n";
    player.update(0.16F);
    std::cout << "Updated position (0.16s dt): (" << player.position.x
              << ", " << player.position.y << ")\n";
    return 0;
}
#endif
