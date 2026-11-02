#include "core.hpp"
#include <iostream>

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
