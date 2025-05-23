// triangle.cpp
// implementation of triangle operations
// calculates face normals for lighting calculations

#include "triangle.h"

Triangle::Triangle(int a, int b, int c) : v0(a), v1(b), v2(c) {}

void Triangle::calculate_normal(const std::vector<Vertex>& vertices) {
    // calculate face normal using cross product of two edges
    // assumes counter-clockwise vertex winding for outward-facing normal
    Vec3 edge1 = vertices[v1].position - vertices[v0].position;
    Vec3 edge2 = vertices[v2].position - vertices[v0].position;
    normal = edge1.cross(edge2).normalize();
}
