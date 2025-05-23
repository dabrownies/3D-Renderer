// vec3.cpp
// implementation of 3d vector operations
// core math functions used throughout the rendering engine

#include "Vec3.h"

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3 Vec3::operator+(const Vec3& other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(float scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::operator*(const Vec3& other) const {
    // element-wise multiplication for color blending
    return Vec3(x * other.x, y * other.y, z * other.z);
}

Vec3 Vec3::operator/(float scalar) const {
    return Vec3(x / scalar, y / scalar, z / scalar);
}

float Vec3::dot(const Vec3& other) const {
    // dot product - measures how aligned two vectors are
    // used for lighting calculations and projections
    return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3& other) const {
    // cross product - gives perpendicular vector
    // essential for calculating surface normals
    return Vec3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

float Vec3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalize() const {
    // convert to unit vector (length = 1)
    // critical for lighting calculations and directions
    float len = length();
    if (len > 0) return *this / len;
    return Vec3(0, 0, 0);
}

Vec3 Vec3::reflect(const Vec3& normal) const {
    // reflect vector across a surface normal
    // used for specular lighting calculations
    return *this - normal * 2.0f * this->dot(normal);
}
