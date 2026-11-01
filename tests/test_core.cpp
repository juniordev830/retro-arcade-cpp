#define RETRO_ARCADE_NO_MAIN
#include "../main.cpp"

#include <cassert>
#include <limits>

int main() {
    Entity entity("test", 1.0F, 2.0F);
    entity.velocity = Vector2(2.0F, -1.0F);
    entity.update(0.5F);
    assert(std::abs(entity.position.x - 2.0F) < 0.0001F);
    assert(std::abs(entity.position.y - 1.5F) < 0.0001F);

    bool rejected = false;
    try { entity.update(-0.1F); } catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);

    rejected = false;
    try { entity.update(std::numeric_limits<float>::infinity()); }
    catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);

    rejected = false;
    try { entity.update(std::numeric_limits<float>::quiet_NaN()); }
    catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);
    return 0;
}
