# Laboratorios de baixo nivel

- Zig: colisao AABB com somas intermediarias em i128 para evitar overflow. Teste: zig test labs/zig/aabb.zig
- Assembly GNU x86-64/System V: soma inteira saturada. Teste em Linux x86-64: gcc -std=c11 -Wall -Wextra -Werror labs/asm/saturating_add_x86_64.S labs/asm/test_saturating_add.c -o /tmp/test_add && /tmp/test_add

Ambos sao experimentos independentes e nao mudam o loop principal do jogo.
