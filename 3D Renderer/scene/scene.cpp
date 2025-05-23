// scene.cpp
// implementation of scene management and demo scene creation
// provides complete scene setup with objects and lighting

#include "scene.h"

Scene::Scene() : camera(Vec3(5, 3, 5), Vec3(0, 0, 0)) {
    create_demo_scene();
}

void Scene::add_mesh(const Mesh& mesh) {
    meshes.push_back(mesh);
}

void Scene::add_light(const Light& light) {
    lights.push_back(light);
}

void Scene::create_demo_scene() {
    // create a variety of materials for visual demonstration
    Material red_material(Vec3(0.8f, 0.2f, 0.2f), Vec3(1, 1, 1), 64.0f);    // shiny red plastic
    Material blue_material(Vec3(0.2f, 0.2f, 0.8f), Vec3(1, 1, 1), 32.0f);   // medium blue
    Material green_material(Vec3(0.2f, 0.8f, 0.2f), Vec3(1, 1, 1), 16.0f);  // matte green
    Material gray_material(Vec3(0.5f, 0.5f, 0.5f), Vec3(0.8f, 0.8f, 0.8f), 128.0f); // very shiny metal
    
    // create and position various geometric objects
    
    // red cube on the left
    Mesh cube = Mesh::create_cube(1.0f, red_material);
    cube.transform = Mat4::translation(Vec3(-2, 0, 0));
    add_mesh(cube);
    
    // blue sphere elevated in center
    Mesh sphere = Mesh::create_sphere(1.0f, 20, blue_material);
    sphere.transform = Mat4::translation(Vec3(0, 1, 0));
    add_mesh(sphere);
    
    // large gray ground plane
    Mesh plane = Mesh::create_plane(10.0f, gray_material);
    plane.transform = Mat4::translation(Vec3(0, -1, 0));
    add_mesh(plane);
    
    // small green accent sphere
    Mesh small_sphere = Mesh::create_sphere(0.5f, 16, green_material);
    small_sphere.transform = Mat4::translation(Vec3(2, 0.5f, -1));
    add_mesh(small_sphere);
    
    // setup lighting with different types and colors
    
    // bright white point light from upper right
    add_light(Light(LightType::POINT, Vec3(3, 4, 2), Vec3(1, 1, 1), 1.0f));
    
    // blue-tinted directional light for fill lighting
    add_light(Light(LightType::DIRECTIONAL, Vec3(-0.5f, -1, -0.3f), Vec3(0.3f, 0.3f, 0.5f), 0.5f));
}

void Scene::render(Renderer& renderer, bool wireframe) {
    // render entire scene with dark blue background
    renderer.clear(Vec3(0.1f, 0.1f, 0.2f));
    
    // render each mesh in the scene
    for (const auto& mesh : meshes) {
        renderer.render_mesh(mesh, camera, lights, wireframe);
    }
}

void Scene::clear_scene() {
    // remove all objects and lights from scene
    meshes.clear();
    lights.clear();
}
