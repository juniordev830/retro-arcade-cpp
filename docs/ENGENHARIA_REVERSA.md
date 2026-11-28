# Engenharia reversa e estudo — Retro Arcade — C++ Core

## Objetivo e fluxo

Movimento 2D e colisão de caixas retangulares. core.hpp define vetores e atualização de entidades. collision.hpp concentra os limites retangulares. Entenda a diferença entre posição, velocidade e área de colisão.

**Tecnologias identificadas** · C++.

**Revisão de referência** · `1cccbee963bf`.

## Mapa do código

| Caminho | Papel de leitura | Símbolos selecionados |
| --- | --- | --- |
| [collision.hpp](../collision.hpp) | Implementação | `AABB2` |
| [core.hpp](../core.hpp) | Implementação | `Vector2`, `Entity`, `update` |
| [main.cpp](../main.cpp) | Ponto de leitura para entrada ou composição | — |

## Configuração e referências

Referências existentes: [docs/GUIA_DE_VALIDACAO.md](GUIA_DE_VALIDACAO.md).

## Roteiro de estudo e desenvolvimento

1. Comece pelo fluxo descrito acima e localize seus pontos de entrada no mapa. Acompanhe uma entrada válida até a transformação ou a resposta.
2. Abra um teste relacionado ao fluxo e descreva qual regra ele protege. Compare o tratamento esperado para entradas válidas, inválidas e nos limites.
3. Ao adicionar uma regra, determine qual módulo controla o dado e cubra o caso nesse nível. Em seguida, confira o efeito no comando, na API ou na interface de entrada.

**Pergunta de entrevista**

Qual resultado o teste deve esperar ao encostar apenas nas bordas de duas caixas?

## Testes versionados

Arquivos para começar a leitura dos cenários de teste: [tests/test_core.cpp](../tests/test_core.cpp).

Os comandos e versões de runtime usados no CI ficam em [.github/workflows/ci.yml](../.github/workflows/ci.yml).

[Voltar ao README](../README.md).
