// vec3.h
// basic 3d vector math operations
// handles positions, directions, normals, and colors in 3d space
// provides all essential vector operations needed for 3d graphics

#ifndef VEC3_H
#define VEC3_H

#include <cmath>

struct Vec3 {
    float x, y, z;
    
    Vec3(float x = 0, float y = 0, float z = 0);
    
    // vector arithmetic operations
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(float scalar) const;
    Vec3 operator*(const Vec3& other) const;  // element-wise multiplication for colors
    Vec3 operator/(float scalar) const;
    
    // essential vector operations for 3d graphics
    float dot(const Vec3& other) const;      // measures alignment between vectors
    Vec3 cross(const Vec3& other) const;     // perpendicular vector for normals
    float length() const;                    // vector magnitude
    Vec3 normalize() const;                  // convert to unit vector
    Vec3 reflect(const Vec3& normal) const;  // reflect across surface normal
};

#endif
