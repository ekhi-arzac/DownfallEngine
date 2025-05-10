# DownfallEngine

A custom graphic engine built with modern C++ and OpenGL.

## Features

- OpenGL rendering pipeline
- ImGui integration for UI
- GLM for mathematics
- Component-based architecture
- Asset management system

## Prerequisites

To build and run DownfallEngine, you need the following dependencies:

- CMake (3.10 or higher)
- C++26 compatible compiler
- OpenGL 4.0+
- GLFW (included as submodule)
- GLM (included as submodule)
- ImGui (included as submodule)

## Building

### Linux

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/DownfallEngine.git
   cd DownfallEngine
   ```

2. Build the project:
   ```bash
   ./build.sh
   ```
   
   Or manually with CMake:
   ```bash
   mkdir -p build
   cd build
   cmake ..
   make
   ```

3. Run the engine:
   ```bash
   cd bin
   ./DownfallEngine
   ```

### Custom Build Options

You can pass additional CMake options for customized builds:

```bash
cmake -DCMAKE_BUILD_TYPE=Release ..  # For release build
```

## Project Structure

- `include/`: Header files
- `src/`: Source files
- `assets/`: Game assets (scenes, shaders, textures, etc.)
- `external/`: Third-party dependencies
- `build/`: Build artifacts (generated)
- `bin/`: Compiled binaries

## License

This project is licensed under the MIT License - see the LICENSE file for details.
