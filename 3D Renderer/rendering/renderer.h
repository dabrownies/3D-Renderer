// renderer.h
// main rendering pipeline and rasterization
// converts 3d geometry to 2d pixels using software rasterization

#ifndef RENDERER_H
#define RENDERER_H

#include "../rendering/framebuffer.h"
#include "../geometry/mesh.h"
#include "../rendering/camera.h"
#include "../lighting/light.h"
#include <vector>

// software rasterizer implementing the 3d graphics pipeline
// transforms geometry, calculates lighting, and rasterizes triangles
class Renderer {
private:
    Framebuffer framebuffer;
    Vec3 ambient_light;  // global ambient lighting

public:
    Renderer(int width, int height);
    
    // main rendering operations
    void clear(const Vec3& color = Vec3(0, 0, 0));
    void render_mesh(const Mesh& mesh, const Camera& camera,
                    const std::vector<Light>& lights,
                    bool wireframe = false, bool flat_shading = true);
    
    // lighting calculations
    Vec3 calculate_lighting(const Vec3& position, const Vec3& normal,
                           const Material& material,
                           const std::vector<Light>& lights,
                           const Vec3& view_dir);
    
    // primitive rendering functions
    void draw_line(Vec3 p1, Vec3 p2, const Vec3& color);
    void draw_triangle_flat(const Vertex& v1, const Vertex& v2, const Vertex& v3,
                           const Vec3& face_normal, const Material& material,
                           const std::vector<Light>& lights, const Vec3& view_dir);
    
    // framebuffer access
    void save_image(const std::string& filename) const;
    Framebuffer& get_framebuffer() { return framebuffer; }
};

#endif
