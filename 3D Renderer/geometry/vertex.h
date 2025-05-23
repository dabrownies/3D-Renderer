// vertex.h
// vertex data structure for 3d geometry
// contains all information needed for a single point in 3d space

#ifndef VERTEX_H
#define VERTEX_H

#include "../math/Vec3.h"

// vertex structure containing position, normal, and color information
// used as building blocks for 3d meshes and geometry
struct Vertex {
    Vec3 position;  // 3d coordinate in space
    Vec3 normal;    // surface normal for lighting calculations
    Vec3 color;     // vertex color (can be overridden by materials)
    
    Vertex(const Vec3& pos = Vec3(), const Vec3& norm = Vec3(), const Vec3& col = Vec3(1, 1, 1));
};

#endif
