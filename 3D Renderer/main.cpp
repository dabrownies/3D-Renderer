// main.cpp
// main application entry point for the 3d rendering engine demo
// demonstrates the engine capabilities with a complete scene

#include "rendering/renderer.h"
#include "scene/scene.h"
#include <iostream>

int main() {
    std::cout << "Starting 3D Rendering Engine..." << std::endl;
    
    // create renderer with specified resolution
    const int width = 800, height = 600;
    Renderer renderer(width, height);
    
    // create and setup demo scene
    Scene scene;
    
    // render scene in solid shading mode
    std::cout << "Rendering solid scene..." << std::endl;
    scene.render(renderer, false);
    renderer.save_image("render_solid.ppm");
    
    // render scene in wireframe mode for comparison
    std::cout << "Rendering wireframe scene..." << std::endl;
    scene.render(renderer, true);
    renderer.save_image("render_wireframe.ppm");
    
    std::cout << "Rendering complete!" << std::endl;
    std::cout << "Output files:" << std::endl;
    std::cout << "- render_solid.ppm (phong shaded)" << std::endl;
    std::cout << "- render_wireframe.ppm (wireframe)" << std::endl;
    
    // display render statistics
    std::cout << "\nRender info:" << std::endl;
    std::cout << "Resolution: " << width << "x" << height << std::endl;
    std::cout << "Objects: " << scene.get_mesh_count() << std::endl;
    std::cout << "Lights: " << scene.get_light_count() << std::endl;
    
    return 0;
}
