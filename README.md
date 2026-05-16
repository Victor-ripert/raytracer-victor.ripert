# Raytracer

A modular, multithreaded Raytracer written in C++20, featuring a dynamic plugin system for primitives.

## Features

- **Multithreaded Rendering:** Automatically scales to use all available CPU cores.
- **Dynamic Plugin System:** Add new shapes (primitives) at runtime without recompiling the core.
- **Configuration Driven:** Define scenes, cameras, and lights using `.cfg` files.
- **Modular Architecture:** Clean separation between the math engine, core renderer, and plugins.

## Prerequisites

- **Compiler:** `g++` with C++20 support.
- **Libraries:** `libconfig++`.
- **Tools:** `make`, `pkg-config`, and `doxygen` (for documentation).

### Installing Dependencies (macOS)
```bash
brew install libconfig doxygen
```

### Installing Dependencies (Ubuntu)
```bash
sudo apt-get install libconfig++-dev doxygen
```

## Building

To build the core engine and the default plugins (Sphere, Plane):
```bash
make
```

To clean the build:
```bash
make fclean
```

## Usage

Run the raytracer by passing a scene configuration file:
```bash
./raytracer scenes/example.cfg
```
The output will be saved as `output.ppm` by default.

## Plugin System: Adding New Primitives

The Raytracer uses a dynamic loading system (`dlopen`). You can add new primitives (like a Cube or Torus) by creating a shared library (`.so`).

### 1. Implementation
Your class must inherit from `RayTracer::IPrimitive` (found in `include/API/IPrimitive.hpp`).

### 2. Required Entry Points
For the factory to load your plugin, you must export these three functions using `extern "C"`:

```cpp
extern "C" {
    // Returns a new instance of your primitive
    RayTracer::IPrimitive *create_primitive() {
        return new MyNewPrimitive();
    }

    // Safely deletes the instance
    void destroy_primitive(RayTracer::IPrimitive *p) {
        delete p;
    }

    // Returns the unique type identifier used in .cfg files
    const char *get_type() {
        return "my_custom_shape";
    }
}
```

### 3. Compilation
Compile your primitive into the `plugins/` directory:
```bash
g++ -shared -fPIC -I./include -o plugins/my_custom_shape.so MyNewPrimitive.cpp src/Math/*.cpp
```

### 4. Usage in Scene
Add it to your `.cfg` file:
```libconfig
primitives = (
    {
        type = "my_custom_shape";
        // ... custom parameters for your shape
    }
);
```

## Documentation

To generate the HTML documentation:
```bash
make doc
```
Then open `docs/html/index.html` in your browser.
