#include "../collision.hpp"

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

    const Vector2 unit = ordinary.normalized();
    assert(std::abs(unit.x - 0.6F) < 0.0001F);
    assert(std::abs(unit.y - 0.8F) < 0.0001F);
    assert(std::abs(ordinary.distanceTo(Vector2(0.0F, 0.0F)) - 5.0F) < 0.0001F);
    const Vector2 zero = Vector2().normalized();
    assert(zero.x == 0.0F && zero.y == 0.0F);

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

    // Zero time must preserve the current position, even with nonzero velocity.
    Entity stationary("stationary", -5.0F, 7.0F);
    stationary.velocity = Vector2(42.0F, -100.0F);
    stationary.update(0.0F);
    assert(stationary.position.x == -5.0F);
    assert(stationary.position.y == 7.0F);

    // Invalid state must be rejected before changing either coordinate.
    Entity invalidPosition("invalid position", 2.0F, 3.0F);
    invalidPosition.position.x = std::numeric_limits<float>::quiet_NaN();
    rejected = false;
    try { invalidPosition.update(0.5F); }
    catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);
    assert(invalidPosition.position.y == 3.0F);

    Entity invalidVelocity("invalid velocity", 2.0F, 3.0F);
    invalidVelocity.velocity.y = std::numeric_limits<float>::infinity();
    rejected = false;
    try { invalidVelocity.update(1.0F); }
    catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);
    assert(invalidVelocity.position.x == 2.0F);
    assert(invalidVelocity.position.y == 3.0F);

    // If only one coordinate overflows, neither coordinate may be committed.
    Entity partialOverflow("partial overflow", 11.0F, std::numeric_limits<float>::max());
    partialOverflow.velocity = Vector2(5.0F, std::numeric_limits<float>::max());
    rejected = false;
    try { partialOverflow.update(2.0F); }
    catch (const std::overflow_error&) { rejected = true; }
    assert(rejected);
    assert(partialOverflow.position.x == 11.0F);
    assert(partialOverflow.position.y == std::numeric_limits<float>::max());

    // AABB collision is symmetric and counts touching edges as contact.
    const AABB2 playerBox(Vector2(10.0F, 10.0F), Vector2(2.0F, 3.0F));
    const AABB2 overlappingBox(Vector2(11.0F, 12.0F), Vector2(1.0F, 1.0F));
    const AABB2 touchingBox(Vector2(13.0F, 10.0F), Vector2(1.0F, 1.0F));
    const AABB2 separatedX(Vector2(13.1F, 10.0F), Vector2(1.0F, 1.0F));
    const AABB2 separatedY(Vector2(10.0F, 14.1F), Vector2(1.0F, 1.0F));
    assert(playerBox.intersects(overlappingBox));
    assert(overlappingBox.intersects(playerBox));
    assert(playerBox.intersects(touchingBox));
    assert(!playerBox.intersects(separatedX));
    assert(!playerBox.intersects(separatedY));

    // Boundary points are contained, while points beyond either axis are not.
    assert(playerBox.contains(Vector2(10.0F, 10.0F)));
    assert(playerBox.contains(Vector2(12.0F, 13.0F)));
    assert(!playerBox.contains(Vector2(12.01F, 13.0F)));
    assert(!playerBox.contains(Vector2(12.0F, 13.01F)));

    // A zero-size box is a valid point collider.
    const AABB2 pointBox(Vector2(-4.0F, 5.0F), Vector2());
    assert(pointBox.contains(Vector2(-4.0F, 5.0F)));
    assert(!pointBox.contains(Vector2(-3.999F, 5.0F)));

    // Constructor validation prevents invalid collision bounds.
    rejected = false;
    try {
        AABB2 invalidCenter(
            Vector2(std::numeric_limits<float>::quiet_NaN(), 0.0F),
            Vector2(1.0F, 1.0F));
    } catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);

    rejected = false;
    try {
        AABB2 negativeExtent(Vector2(), Vector2(-1.0F, 1.0F));
    } catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);

    rejected = false;
    try {
        AABB2 infiniteExtent(
            Vector2(),
            Vector2(1.0F, std::numeric_limits<float>::infinity()));
    } catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);

    // Double intermediates keep extreme finite centers comparable.
    const AABB2 farPositive(
        Vector2(std::numeric_limits<float>::max(), 0.0F), Vector2());
    const AABB2 farNegative(
        Vector2(-std::numeric_limits<float>::max(), 0.0F), Vector2());
    assert(!farPositive.intersects(farNegative));

    return 0;
}
