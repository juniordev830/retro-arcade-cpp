# Retro Arcade — C++ Core

Exercício em C++17 que explora operações vetoriais 2D, atualização de posição de entidades usando velocidade e delta time, e colisão entre hitboxes retangulares.

> O código atual é um exemplo de núcleo de simulação em console; ainda não é uma engine gráfica completa nem implementa um sistema ECS.

## Requisitos

- Compilador C++ com suporte a C++17 (por exemplo, GCC ou Clang)

## Compilar e executar

Linux/macOS:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o arcade_engine
./arcade_engine
```

Windows com MinGW:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o arcade_engine.exe
.\\arcade_engine.exe
```

## Testes

Os testes cobrem soma e magnitude vetorial (incluindo valores grandes que podem causar overflow intermediário), atualização de posição, rejeição de delta time inválido e prevenção de overflow da posição.

Linux/macOS:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic tests/test_core.cpp -o test_core
./test_core
```

## Integração contínua

O GitHub Actions compila o exemplo e a suíte de regressão com avisos tratados como erros e executa ambos em pushes para `main` e em pull requests.

## Conceitos implementados

- Tipo `Vector2` com soma e cálculo de magnitude.
- Entidade com posição e velocidade.
- Atualização de posição usando delta time.
- Hitboxes `AABB2` para detectar sobreposição e verificar se um ponto está dentro de um retângulo.
- Validação de valores não finitos e prevenção de overflow de posição.
- Demonstração no terminal.

## Organização

- `core.hpp`: tipos reutilizáveis `Vector2` e `Entity`, independentes do executável.
- `collision.hpp`: colisão 2D por retângulos alinhados aos eixos.
- `main.cpp`: demonstração no terminal.
- `tests/test_core.cpp`: testes que incluem diretamente o núcleo.

## Próximas melhorias

- Expandir os testes para limites adicionais de vetores e cenários extremos de atualização.
- Adicionar CMake quando o projeto crescer.
- Introduzir renderização somente quando houver uma biblioteca gráfica definida.

Projeto de aprendizagem em evolução.
