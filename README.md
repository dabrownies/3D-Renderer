# 3D Rendering Engine

A complete 3D software rasterizer built from scratch in C++. Renders geometric shapes with realistic lighting and materials using CPU-based triangle rasterization.

## What It Does

This rendering engine implements the full 3D graphics pipeline without GPU acceleration. Converts 3D geometry into 2D pixels using mathematical transformations and lighting calculations.

### Features

- **Geometric Primitives** - Cubes, spheres, and planes with procedural generation
- **Phong Lighting Model** - Ambient, diffuse, and specular lighting components
- **Multiple Light Types** - Point lights with falloff and directional lights
- **Material System** - Configurable surface properties (shininess, color, reflectance)
- **Camera Controls** - Perspective projection and orbital navigation
- **Depth Testing** - Z-buffer for proper hidden surface removal
- **Wireframe Mode** - Toggle between solid and outline rendering
- **Flat Shading** - Per-triangle lighting calculations

## How It Works

1. **Geometry Setup** - Create meshes from vertices and triangles
2. **Transformation Pipeline** - Model → World → View → Projection → Screen space
3. **Lighting Calculation** - Phong model with multiple light sources
4. **Rasterization** - Convert triangles to pixels using scanline algorithm
5. **Depth Testing** - Z-buffer ensures correct visibility
6. **Output** - Generate PPM image files

The engine uses matrix mathematics for 3D transformations and implements barycentric coordinates for triangle rasterization.

## Getting Started

### Requirements

- C++17 compatible compiler (g++, clang++)
- Make build system

### Building

```bash
make          # compile the engine
make run      # build and run demo
make clean    # remove build files
```

### Quick Test

```bash
./render_engine
```

Creates two output files:
- `render_solid.ppm` - Full shaded rendering
- `render_wireframe.ppm` - Outline view

## File Structure

The engine is organized into modular components:

- **math/** - Vector and matrix operations
- **geometry/** - Vertices, triangles, meshes, materials
- **lighting/** - Light sources and types
- **rendering/** - Camera, framebuffer, main renderer
- **scene/** - Scene management and demo setup

## Customizing Scenes

### Adding Objects

```cpp
// Create materials
Material red_plastic(Vec3(0.8f, 0.2f, 0.2f), Vec3(1, 1, 1), 64.0f);
Material shiny_metal(Vec3(0.7f, 0.7f, 0.7f), Vec3(1, 1, 1), 128.0f);

// Create and position objects
Mesh cube = Mesh::create_cube(1.0f, red_plastic);
cube.transform = Mat4::translation(Vec3(2, 0, -3));
scene.add_mesh(cube);

Mesh sphere = Mesh::create_sphere(1.0f, 20, shiny_metal);
sphere.transform = Mat4::scale(Vec3(1.5f, 1.5f, 1.5f));
scene.add_mesh(sphere);
```

### Lighting Setup

```cpp
// Point light with warm color
scene.add_light(Light(LightType::POINT, Vec3(3, 4, 2), Vec3(1, 0.8f, 0.6f), 1.0f));

// Directional light for fill lighting
scene.add_light(Light(LightType::DIRECTIONAL, Vec3(-0.5f, -1, -0.3f), Vec3(0.4f, 0.4f, 0.6f), 0.5f));
```

### Camera Movement

```cpp
// Position camera
camera.position = Vec3(5, 3, 5);
camera.target = Vec3(0, 0, 0);

// Orbital rotation
camera.rotate_around_target(0.1f, 0.05f);

// Forward/backward movement
camera.move_forward(2.0f);
```

## Performance Notes

- **Resolution** - Higher resolution = longer render times
- **Triangle Count** - More detailed meshes increase computation
- **Light Count** - Each light adds to per-pixel calculations
- **Typical Times** - 800x600 renders in 1-5 seconds on modern CPUs

## Technical Implementation

### Graphics Pipeline

The engine implements a traditional software rendering pipeline:

1. **Vertex Processing** - Transform vertices through MVP matrices
2. **Primitive Assembly** - Group vertices into triangles
3. **Clipping** - Remove geometry outside view frustum
4. **Rasterization** - Convert triangles to pixels
5. **Fragment Processing** - Calculate per-pixel lighting
6. **Depth Testing** - Z-buffer hidden surface removal

### Lighting Model

Uses Phong reflection model with three components:
- **Ambient** - Base illumination level
- **Diffuse** - Surface brightness based on light angle (Lambertian)
- **Specular** - Shiny highlights based on view angle

### Coordinate Systems

- **Model Space** - Object's local coordinates
- **World Space** - Scene's global coordinates  
- **View Space** - Camera-relative coordinates
- **Clip Space** - Perspective projection applied
- **Screen Space** - Final 2D pixel coordinates

## License

MIT License - Free to use and modify
