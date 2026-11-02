#include "../core.hpp"

#include <cassert>
#include <limits>

int main() {
    const Vector2 ordinary(3.0F, 4.0F);
    assert(std::abs(ordinary.magnitude() - 5.0F) < 0.0001F);

    // Squaring 1e20F overflows float even though the magnitude is representable.
    const Vector2 large(1.0e20F, 0.0F);
    assert(std::isfinite(large.magnitude()));
    assert(std::abs(large.magnitude() / 1.0e20F - 1.0F) < 0.0001F);

    const Vector2 sum = Vector2(1.0F, 2.0F) + Vector2(3.0F, 4.0F);
    assert(sum.x == 4.0F);
    assert(sum.y == 6.0F);

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

    Entity overflow("overflow", std::numeric_limits<float>::max() / 2.0F, 0.0F);
    overflow.velocity = Vector2(std::numeric_limits<float>::max() / 2.0F, 0.0F);
    rejected = false;
    try { overflow.update(2.0F); } catch (const std::overflow_error&) { rejected = true; }
    assert(rejected);
    assert(overflow.position.x == std::numeric_limits<float>::max() / 2.0F);
    return 0;
}
