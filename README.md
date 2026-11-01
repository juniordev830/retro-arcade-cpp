# Retro Arcade — C++ Core

Exercício em C++17 que explora operações vetoriais 2D e atualização de posição de uma entidade usando velocidade e delta time.

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
.\arcade_engine.exe
```

## Testes

O teste existente cobre atualização de posição e rejeição de delta time negativo ou não finito.

Linux/macOS:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic tests/test_core.cpp -o test_core
./test_core
```

## Conceitos implementados

- Tipo `Vector2` com soma e cálculo de magnitude.
- Entidade com posição e velocidade.
- Atualização de posição usando delta time.
- Validação de valores não finitos e prevenção de overflow de posição.
- Demonstração no terminal.

## Próximas melhorias

- Expandir os testes para magnitude vetorial, soma e overflow de coordenadas.
- Separar os tipos em módulos e adicionar CMake quando o projeto crescer.
- Introduzir renderização somente quando houver uma biblioteca gráfica definida.

Projeto de aprendizagem em evolução.
