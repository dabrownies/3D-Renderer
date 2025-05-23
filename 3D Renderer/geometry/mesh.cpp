// mesh.cpp
// implementation of 3d mesh operations and primitive generation
// provides factory methods for common geometric shapes

#include "mesh.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Mesh::Mesh(const Material& mat) : material(mat) {}

void Mesh::add_vertex(const Vertex& vertex) {
    vertices.push_back(vertex);
}

void Mesh::add_triangle(int v0, int v1, int v2) {
    // create triangle and calculate its face normal
    Triangle tri(v0, v1, v2);
    tri.calculate_normal(vertices);
    triangles.push_back(tri);
}

void Mesh::calculate_vertex_normals() {
    // calculate smooth vertex normals by averaging adjacent face normals
    // this creates smoother lighting compared to flat face normals
    
    // reset all vertex normals to zero
    for (auto& vertex : vertices) {
        vertex.normal = Vec3(0, 0, 0);
    }
    
    // accumulate face normals for each vertex
    for (const auto& tri : triangles) {
        vertices[tri.v0].normal = vertices[tri.v0].normal + tri.normal;
        vertices[tri.v1].normal = vertices[tri.v1].normal + tri.normal;
        vertices[tri.v2].normal = vertices[tri.v2].normal + tri.normal;
    }
    
    // normalize all accumulated normals
    for (auto& vertex : vertices) {
        vertex.normal = vertex.normal.normalize();
    }
}

Mesh Mesh::create_cube(float size, const Material& mat) {
    // generate cube mesh with 8 vertices and 12 triangles
    Mesh cube(mat);
    float half = size * 0.5f;
    
    // define 8 corner vertices of a cube centered at origin
    Vec3 positions[8] = {
        Vec3(-half, -half, -half), Vec3(half, -half, -half),  // bottom face
        Vec3(half, half, -half), Vec3(-half, half, -half),
        Vec3(-half, -half, half), Vec3(half, -half, half),    // top face
        Vec3(half, half, half), Vec3(-half, half, half)
    };
    
    for (int i = 0; i < 8; i++) {
        cube.add_vertex(Vertex(positions[i]));
    }
    
    // define 12 triangles (2 per face) with counter-clockwise winding
    int faces[12][3] = {
        {0, 1, 2}, {0, 2, 3}, // front face
        {5, 4, 7}, {5, 7, 6}, // back face
        {4, 0, 3}, {4, 3, 7}, // left face
        {1, 5, 6}, {1, 6, 2}, // right face
        {3, 2, 6}, {3, 6, 7}, // top face
        {4, 5, 1}, {4, 1, 0}  // bottom face
    };
    
    for (int i = 0; i < 12; i++) {
        cube.add_triangle(faces[i][0], faces[i][1], faces[i][2]);
    }
    
    cube.calculate_vertex_normals();
    return cube;
}

Mesh Mesh::create_sphere(float radius, int segments, const Material& mat) {
    // generate sphere using latitude/longitude subdivision
    // creates smooth sphere with configurable detail level
    Mesh sphere(mat);
    
    // generate vertices using spherical coordinates
    for (int lat = 0; lat <= segments; lat++) {
        float theta = (float)lat * M_PI / segments;        // latitude angle
        float sin_theta = std::sin(theta);
        float cos_theta = std::cos(theta);
        
        for (int lon = 0; lon <= segments; lon++) {
            float phi = (float)lon * 2.0f * M_PI / segments;  // longitude angle
            float sin_phi = std::sin(phi);
            float cos_phi = std::cos(phi);
            
            // convert spherical coordinates to cartesian
            Vec3 pos(
                radius * sin_theta * cos_phi,
                radius * cos_theta,
                radius * sin_theta * sin_phi
            );
            
            // for a sphere, the normal equals the normalized position
            sphere.add_vertex(Vertex(pos, pos.normalize()));
        }
    }
    
    // connect vertices with triangles in a grid pattern
    for (int lat = 0; lat < segments; lat++) {
        for (int lon = 0; lon < segments; lon++) {
            // calculate vertex indices for current grid square
            int v0 = lat * (segments + 1) + lon;
            int v1 = v0 + segments + 1;
            int v2 = v0 + 1;
            int v3 = v1 + 1;
            
            // create two triangles per grid square
            sphere.add_triangle(v0, v1, v2);
            sphere.add_triangle(v2, v1, v3);
        }
    }
    
    return sphere;
}

Mesh Mesh::create_plane(float size, const Material& mat) {
    // create simple flat plane (useful for floors, walls, etc.)
    Mesh plane(mat);
    float half = size * 0.5f;
    
    // create 4 corner vertices for a flat square in xz plane
    plane.add_vertex(Vertex(Vec3(-half, 0, -half), Vec3(0, 1, 0)));  // bottom-left
    plane.add_vertex(Vertex(Vec3(half, 0, -half), Vec3(0, 1, 0)));   // bottom-right
    plane.add_vertex(Vertex(Vec3(half, 0, half), Vec3(0, 1, 0)));    // top-right
    plane.add_vertex(Vertex(Vec3(-half, 0, half), Vec3(0, 1, 0)));   // top-left
    
    // connect vertices into two triangles
    plane.add_triangle(0, 1, 2);  // first triangle
    plane.add_triangle(0, 2, 3);  // second triangle
    
    return plane;
}
