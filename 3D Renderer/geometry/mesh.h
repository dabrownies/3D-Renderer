// mesh.h
// 3d mesh class for representing geometric objects
// contains vertices, triangles, materials, and transformation data

#ifndef MESH_H
#define MESH_H

#include "vertex.h"
#include "triangle.h"
#include "material.h"
#include "../math/mat4.h"
#include <vector>

// 3d mesh class representing complete geometric objects
// combines vertices, triangles, material properties, and transformations
class Mesh {
public:
    std::vector<Vertex> vertices;     // all vertex data for this mesh
    std::vector<Triangle> triangles;  // triangle faces connecting vertices
    Material material;                // surface appearance properties
    Mat4 transform;                   // object-to-world transformation matrix
    
    Mesh(const Material& mat = Material());
    
    // mesh construction methods
    void add_vertex(const Vertex& vertex);           // add single vertex
    void add_triangle(int v0, int v1, int v2);       // connect three vertices
    void calculate_vertex_normals();                 // compute smooth normals
    
    // factory methods for creating common geometric primitives
    static Mesh create_cube(float size = 1.0f, const Material& mat = Material());
    static Mesh create_sphere(float radius = 1.0f, int segments = 16, const Material& mat = Material());
    static Mesh create_plane(float size = 2.0f, const Material& mat = Material());
};

#endif
