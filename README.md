# Flappy Bird Clone

A C++ and SDL2-powered clone of the classic Flappy Bird game. This project serves as a fun way to learn game development
and explore the power of SDL2 for 2D graphics and game mechanics.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Building the Project](#building-the-project)
    - [Running the Game](#running-the-game)
- [Gameplay](#gameplay)
- [Contributing](#contributing)
- [License](#license)

---

## Features

- Simple and responsive gameplay mechanics.
- Dynamic and procedurally generated obstacles.
- Realistic physics for player movement.
- Scoring system and high score tracking.
- Easy to modify and extend.

---

## Getting Started

### Prerequisites

Ensure you have the following installed on your system:

- **C++ Compiler** (e.g., GCC, Clang, or MSVC)
- **CMake** (3.10 or newer)
- **SDL2** development libraries
- **SDL2_image** (for loading textures)

On Ubuntu/Debian-based systems, you can install the dependencies with:

```bash
sudo apt-get install libsdl2-dev libsdl2-image-dev cmake g++
```

## Building the Project

1. Clone the repository:

```bash

git clone https://github.com/riebers-m/FlappyBird.git
cd FlappyBird
```

2. Create a build directory:

```bash
mkdir build && cd build
```

3. Configure the project with CMake:

```bash
cmake ..
```

4. Build the game:

```bash
    cmake --build .
```

## Gameplay

* Controls: Press the spacebar to make the bird flap.
* Objective: Avoid obstacles and keep the bird flying as long as possible.
* Scoring: Gain points by passing through obstacles.

## License

This project is licensed under the MIT License. See the [LICENSE](#LI) file for details.

## Acknowledgments

    Original Flappy Bird game by Dong Nguyen.
    Built with SDL2.