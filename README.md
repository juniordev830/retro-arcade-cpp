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

## Conceitos implementados

- Tipo `Vector2` com soma e cálculo de magnitude.
- Entidade com posição e velocidade.
- Atualização de posição usando delta time.
- Demonstração no terminal.

## Próximas melhorias

- Adicionar testes unitários para operações vetoriais.
- Validar delta time e valores não finitos.
- Separar os tipos em módulos e adicionar CMake quando o projeto crescer.
- Introduzir renderização somente quando houver uma biblioteca gráfica definida.

Projeto de aprendizagem em evolução.
