# SmoothLife Project

SmoothLife is a project that simulates a smooth version of Conway's Game of Life. This project implements the SmoothLife algorithm and provides a graphical interface to visualize the simulation.

## Features

- Implementation of the SmoothLife algorithm
- Graphical user interface for visualization
- Adjustable parameters for the simulation

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Vetterli65/smoothlife.git
   cd smoothlife
   ```
2. Ensure you have the necessary dependencies installed. This project requires:
    * A C++ compiler (e.g., g++, clang++)
    * Raylib and RayGUI included as dependencies in Cmake file
3. Naviagate to the build directory:
    ```bash
    cd build
    ```
4. Run CMake to configure the project:
    ```bash
    cmake ..
    ```
5. Build the project:
    ```bash
    cmake --build .
    ```
6. Run the executable:
    ```bash
    ./smoothlife

## Usage

The **main.cpp** file contains an example of how to set up and run the SmoothLife simulation. Below is a brief explanation of the key components and how to use them.

### Example

The example in **main.cpp** demonstrates setting up the simulation and running it with a graphical interface.

```cpp
#include "scene.h"

int main() {
    int WIDTH = 1440;
    int HEIGHT = 960;

    Scene scene(WIDTH, HEIGHT);

    scene.run();

    return 0;
}
```

### Adjusting Parameters

You can adjust the simulation parameters by modifying the parameters inside the rendering window. This allows you to experiment with different settings and observe their effects on the simulation.

### References

* Stephan Rafler, "Generalization of Conway's "Game of Life" to a Continuous Domain - SmoothLife," arXiv:1106.1640, 2011. [Link](http://arxiv.org/pdf/1111.1567)