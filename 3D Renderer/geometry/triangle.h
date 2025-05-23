// triangle.h
// triangle face structure for 3d meshes
// connects three vertices and calculates surface normals

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../math/Vec3.h"
#include "vertex.h"
#include <vector>

// triangle structure representing a single face in a 3d mesh
// stores vertex indices and calculates face normal for lighting
struct Triangle {
    int v0, v1, v2;  // indices into vertex array (counter-clockwise winding)
    Vec3 normal;     // face normal vector for flat shading
    
    Triangle(int a, int b, int c);
    
    // calculate face normal from three vertices using cross product
    void calculate_normal(const std::vector<Vertex>& vertices);
};

#endif
