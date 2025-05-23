// vertex.cpp
// implementation of vertex structure
// simple constructor for vertex data

#include "vertex.h"

Vertex::Vertex(const Vec3& pos, const Vec3& norm, const Vec3& col)
    : position(pos), normal(norm), color(col) {
}
