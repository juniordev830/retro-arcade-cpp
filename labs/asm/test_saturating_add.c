#include <assert.h>
#include <limits.h>
#include <stdio.h>

extern long long saturating_add_i64(long long left, long long right);

int main(void) {
    assert(saturating_add_i64(7, 3) == 10);
    assert(saturating_add_i64(LLONG_MAX, 1) == LLONG_MAX);
    assert(saturating_add_i64(LLONG_MIN, -1) == LLONG_MIN);
    assert(saturating_add_i64(LLONG_MIN, LLONG_MAX) == -1);
    puts("Assembly saturated-add checks passed");
    return 0;
}
