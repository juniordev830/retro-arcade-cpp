# Verificação e evolução — Retro Arcade C++

## Escopo confirmado

Núcleo de simulação vetorial e colisões AABB em C++17; demonstração em console.

## Localização do código

`main.cpp`, `core.hpp`, `collision.hpp`, `tests/test_core.cpp`.

## Verificar localmente

`g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o arcade_engine`; executar `./arcade_engine`; compilar testes de `tests/test_core.cpp` com C++17.

Use dados fictícios e registre no PR o comando, ambiente e resultado observado. Para projetos sem runtime instalado, marque a verificação como pendente em vez de afirmar que passou.

## Casos de regressão a cobrir

Testar delta time negativo, NaN e infinito, colisão somente por borda, magnitudes altas e atualização sem overflow.

## Limitações e próximo incremento

Separar matemática de renderização; qualquer engine gráfica futura deve consumir contratos já testados.

## Critérios de revisão

- [ ] O comportamento alterado está descrito com exemplo reproduzível.
- [ ] Há teste ou procedimento de validação compatível com o código real.
- [ ] Nenhuma chave, dado pessoal ou arquivo gerado foi incluído sem necessidade.
- [ ] A documentação distingue o implementado do planejado.
