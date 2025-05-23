// scene.h
// scene management and organization
// contains all objects, lights, and camera for a complete 3d scene

#ifndef SCENE_H
#define SCENE_H

#include "../geometry/mesh.h"
#include "../lighting/light.h"
#include "../rendering/camera.h"
#include "../rendering/renderer.h"
#include <vector>

// scene class managing all elements of a 3d scene
// provides high-level interface for scene setup and rendering
class Scene {
public:
    std::vector<Mesh> meshes;   // all 3d objects in the scene
    std::vector<Light> lights;  // all light sources
    Camera camera;              // viewpoint for rendering
    
    Scene();
    
    // scene setup methods
    void add_mesh(const Mesh& mesh);        // add 3d object to scene
    void add_light(const Light& light);     // add light source
    void create_demo_scene();               // setup example scene with various objects
    
    // rendering methods
    void render(Renderer& renderer, bool wireframe = false);  // render entire scene
    void clear_scene();                                       // remove all objects and lights
    
    // scene information
    size_t get_mesh_count() const { return meshes.size(); }
    size_t get_light_count() const { return lights.size(); }
};

#endif
