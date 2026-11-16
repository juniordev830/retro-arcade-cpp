const std = @import("std");

pub const Box = struct {
    x: i64,
    y: i64,
    width: u64,
    height: u64,
};

/// Integer-safe axis-aligned collision detection. Touching edges do not collide.
pub fn overlaps(a: Box, b: Box) bool {
    if (a.width == 0 or a.height == 0 or b.width == 0 or b.height == 0) return false;
    const ax2: i128 = @as(i128, a.x) + @as(i128, a.width);
    const ay2: i128 = @as(i128, a.y) + @as(i128, a.height);
    const bx2: i128 = @as(i128, b.x) + @as(i128, b.width);
    const by2: i128 = @as(i128, b.y) + @as(i128, b.height);
    return @as(i128, a.x) < bx2 and @as(i128, b.x) < ax2 and
        @as(i128, a.y) < by2 and @as(i128, b.y) < ay2;
}

test "overlap, edge contact and extreme coordinates" {
    const a = Box{ .x = 0, .y = 0, .width = 10, .height = 10 };
    try std.testing.expect(overlaps(a, .{ .x = 9, .y = 9, .width = 3, .height = 3 }));
    try std.testing.expect(!overlaps(a, .{ .x = 10, .y = 0, .width = 3, .height = 3 }));
    try std.testing.expect(!overlaps(a, .{ .x = 0, .y = 0, .width = 0, .height = 3 }));
    try std.testing.expect(!overlaps(.{ .x = std.math.maxInt(i64), .y = 0, .width = 5, .height = 5 }, a));
}
