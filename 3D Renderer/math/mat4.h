// mat4.h
// 4x4 transformation matrix operations
// handles rotation, translation, scaling, and projection transformations
// core of the 3d graphics transformation pipeline

#ifndef MAT4_H
#define MAT4_H

#include "Vec3.h"

struct Mat4 {
    float m[16];  // stored in column-major order for opengl compatibility
    
    Mat4();  // initialize as identity matrix
    Mat4(float values[16]);
    
    // matrix operations
    Mat4 operator*(const Mat4& other) const;  // combine transformations
    
    // transform 3d vectors through the matrix
    Vec3 transform_point(const Vec3& point) const;      // includes translation
    Vec3 transform_direction(const Vec3& dir) const;    // no translation for normals
    
    // factory methods for common transformations
    static Mat4 translation(const Vec3& t);                                    // move objects
    static Mat4 rotation_y(float angle);                                       // rotate around y-axis
    static Mat4 scale(const Vec3& s);                                         // resize objects
    static Mat4 perspective(float fov, float aspect, float near, float far);  // perspective projection
    static Mat4 look_at(const Vec3& eye, const Vec3& target, const Vec3& up); // camera view matrix
};

#endif
