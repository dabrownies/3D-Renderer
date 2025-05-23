// renderer.cpp
// implementation of the 3d rendering pipeline
// handles geometry transformation, lighting, and rasterization

#include "renderer.h"
#include <algorithm>
#include <cmath>

Renderer::Renderer(int width, int height)
    : framebuffer(width, height), ambient_light(0.2f, 0.2f, 0.2f) {}

void Renderer::clear(const Vec3& color) {
    framebuffer.clear(color);
}

Vec3 Renderer::calculate_lighting(const Vec3& position, const Vec3& normal,
                                 const Material& material,
                                 const std::vector<Light>& lights,
                                 const Vec3& view_dir) {
    // implement phong lighting model with ambient, diffuse, and specular components
    
    // start with ambient lighting contribution
    Vec3 final_color = ambient_light * material.diffuse_color * material.ambient_strength;
    
    // add contribution from each light source
    for (const auto& light : lights) {
        Vec3 light_dir;
        float attenuation = 1.0f;
        
        if (light.type == LightType::POINT) {
            // point light: calculate direction and distance attenuation
            Vec3 light_vec = light.position - position;
            float distance = light_vec.length();
            light_dir = light_vec / distance;
            
            // quadratic attenuation formula for realistic falloff
            attenuation = 1.0f / (1.0f + 0.1f * distance + 0.01f * distance * distance);
        } else {
            // directional light: constant direction, no attenuation
            light_dir = light.direction * -1.0f;
        }
        
        // diffuse lighting using lambert's cosine law
        float diffuse_intensity = std::max(0.0f, normal.dot(light_dir));
        Vec3 diffuse = material.diffuse_color * light.color * diffuse_intensity;
        
        // specular lighting using phong reflection model
        Vec3 reflect_dir = (light_dir * -1.0f).reflect(normal);
        float specular_intensity = std::pow(std::max(0.0f, view_dir.dot(reflect_dir)), material.shininess);
        Vec3 specular = material.specular_color * light.color * specular_intensity;
        
        // combine diffuse and specular with attenuation and light intensity
        final_color = final_color + (diffuse + specular) * light.intensity * attenuation;
    }
    
    return final_color;
}

void Renderer::draw_line(Vec3 p1, Vec3 p2, const Vec3& color) {
    // simple bresenham line algorithm for wireframe rendering
    int x1 = (int)p1.x, y1 = (int)p1.y;
    int x2 = (int)p2.x, y2 = (int)p2.y;
    
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    
    while (true) {
        framebuffer.set_pixel(x1, y1, color, p1.z);
        
        if (x1 == x2 && y1 == y2) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

void Renderer::draw_triangle_flat(const Vertex& v1, const Vertex& v2, const Vertex& v3,
                                 const Vec3& face_normal, const Material& material,
                                 const std::vector<Light>& lights, const Vec3& view_dir) {
    // flat shading: calculate lighting once at triangle center
    Vec3 center = (v1.position + v2.position + v3.position) / 3.0f;
    Vec3 color = calculate_lighting(center, face_normal, material, lights, view_dir);
    
    // sort vertices by y coordinate for scanline algorithm
    std::vector<Vec3> points = {v1.position, v2.position, v3.position};
    std::sort(points.begin(), points.end(), [](const Vec3& a, const Vec3& b) {
        return a.y < b.y;
    });
    
    // triangle rasterization using barycentric coordinates
    for (int y = (int)points[0].y; y <= (int)points[2].y; y++) {
        for (int x = (int)std::min({points[0].x, points[1].x, points[2].x});
             x <= (int)std::max({points[0].x, points[1].x, points[2].x}); x++) {
            
            // point-in-triangle test using barycentric coordinates
            Vec3 p(x, y, 0);
            Vec3 v0 = points[2] - points[0];
            Vec3 v1 = points[1] - points[0];
            Vec3 v2 = p - points[0];
            
            float dot00 = v0.dot(v0);
            float dot01 = v0.dot(v1);
            float dot02 = v0.dot(v2);
            float dot11 = v1.dot(v1);
            float dot12 = v1.dot(v2);
            
            float inv_denom = 1 / (dot00 * dot11 - dot01 * dot01);
            float u = (dot11 * dot02 - dot01 * dot12) * inv_denom;
            float v = (dot00 * dot12 - dot01 * dot02) * inv_denom;
            
            // if point is inside triangle, render pixel with interpolated depth
            if (u >= 0 && v >= 0 && u + v <= 1) {
                float z = points[0].z + u * (points[2].z - points[0].z) + v * (points[1].z - points[0].z);
                framebuffer.set_pixel(x, y, color, z);
            }
        }
    }
}

void Renderer::render_mesh(const Mesh& mesh, const Camera& camera,
                          const std::vector<Light>& lights,
                          bool wireframe, bool flat_shading) {
    // main mesh rendering function implementing the graphics pipeline
    
    // combine model, view, and projection transformations
    Mat4 mvp = camera.get_projection_matrix() * camera.get_view_matrix() * mesh.transform;
    Mat4 model_view = camera.get_view_matrix() * mesh.transform;
    
    // transform all vertices from model space to screen space
    std::vector<Vertex> transformed_vertices;
    for (const auto& vertex : mesh.vertices) {
        Vertex transformed = vertex;
        
        // apply full transformation pipeline
        Vec3 world_pos = mesh.transform.transform_point(vertex.position);
        Vec3 view_pos = model_view.transform_point(vertex.position);
        Vec3 clip_pos = mvp.transform_point(vertex.position);
        
        // perspective divide and viewport transformation
        if (clip_pos.z != 0) {
            transformed.position.x = (clip_pos.x / clip_pos.z + 1.0f) * framebuffer.get_width() * 0.5f;
            transformed.position.y = (1.0f - clip_pos.y / clip_pos.z) * framebuffer.get_height() * 0.5f;
            transformed.position.z = clip_pos.z;
        }
        
        // transform normal vector for lighting calculations
        transformed.normal = mesh.transform.transform_direction(vertex.normal).normalize();
        
        transformed_vertices.push_back(transformed);
    }
    
    Vec3 view_dir = (camera.target - camera.position).normalize();
    
    // render each triangle in the mesh
    for (const auto& triangle : mesh.triangles) {
        const Vertex& v1 = transformed_vertices[triangle.v0];
        const Vertex& v2 = transformed_vertices[triangle.v1];
        const Vertex& v3 = transformed_vertices[triangle.v2];
        
        // back-face culling - skip triangles facing away from camera
        Vec3 edge1 = v2.position - v1.position;
        Vec3 edge2 = v3.position - v1.position;
        Vec3 screen_normal = edge1.cross(edge2);
        
        if (screen_normal.z > 0) continue;  // triangle faces away from camera
        
        if (wireframe) {
            // wireframe mode: render triangle edges only
            draw_line(v1.position, v2.position, Vec3(1, 1, 1));
            draw_line(v2.position, v3.position, Vec3(1, 1, 1));
            draw_line(v3.position, v1.position, Vec3(1, 1, 1));
        } else {
            // solid mode: fill triangle with computed lighting
            Vec3 world_normal = mesh.transform.transform_direction(triangle.normal).normalize();
            draw_triangle_flat(v1, v2, v3, world_normal, mesh.material, lights, view_dir);
        }
    }
}

void Renderer::save_image(const std::string& filename) const {
    framebuffer.save_ppm(filename);
}
