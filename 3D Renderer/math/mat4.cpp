// mat4.cpp
// implementation of 4x4 matrix operations
// provides all transformation functions needed for 3d graphics pipeline

#include "mat4.h"
#include <cmath>

Mat4::Mat4() {
    // initialize as identity matrix (no transformation)
    for (int i = 0; i < 16; i++) m[i] = 0;
    m[0] = m[5] = m[10] = m[15] = 1;
}

Mat4::Mat4(float values[16]) {
    for (int i = 0; i < 16; i++) m[i] = values[i];
}

Mat4 Mat4::operator*(const Mat4& other) const {
    // matrix multiplication - combines transformations
    // order matters: this * other applies 'other' first, then 'this'
    Mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i * 4 + j] = 0;
            for (int k = 0; k < 4; k++) {
                result.m[i * 4 + j] += m[i * 4 + k] * other.m[k * 4 + j];
            }
        }
    }
    return result;
}

Vec3 Mat4::transform_point(const Vec3& point) const {
    // transform a 3d point including translation component
    float x = m[0] * point.x + m[1] * point.y + m[2] * point.z + m[3];
    float y = m[4] * point.x + m[5] * point.y + m[6] * point.z + m[7];
    float z = m[8] * point.x + m[9] * point.y + m[10] * point.z + m[11];
    float w = m[12] * point.x + m[13] * point.y + m[14] * point.z + m[15];
    
    // perspective divide for projection matrices
    if (w != 0) return Vec3(x / w, y / w, z / w);
    return Vec3(x, y, z);
}

Vec3 Mat4::transform_direction(const Vec3& dir) const {
    // transform direction vector without translation (for normals and directions)
    return Vec3(
        m[0] * dir.x + m[1] * dir.y + m[2] * dir.z,
        m[4] * dir.x + m[5] * dir.y + m[6] * dir.z,
        m[8] * dir.x + m[9] * dir.y + m[10] * dir.z
    );
}

Mat4 Mat4::translation(const Vec3& t) {
    // create translation matrix to move objects in 3d space
    Mat4 result;
    result.m[3] = t.x;
    result.m[7] = t.y;
    result.m[11] = t.z;
    return result;
}

Mat4 Mat4::rotation_y(float angle) {
    // create rotation matrix around y-axis (vertical rotation)
    Mat4 result;
    float c = std::cos(angle);
    float s = std::sin(angle);
    result.m[0] = c; result.m[2] = s;
    result.m[8] = -s; result.m[10] = c;
    return result;
}

Mat4 Mat4::scale(const Vec3& s) {
    // create scale matrix to resize objects
    Mat4 result;
    result.m[0] = s.x;
    result.m[5] = s.y;
    result.m[10] = s.z;
    return result;
}

Mat4 Mat4::perspective(float fov, float aspect, float near, float far) {
    // create perspective projection matrix for realistic depth
    Mat4 result;
    float tan_half_fov = std::tan(fov / 2.0f);
    
    result.m[0] = 1.0f / (aspect * tan_half_fov);
    result.m[5] = 1.0f / tan_half_fov;
    result.m[10] = -(far + near) / (far - near);
    result.m[11] = -(2.0f * far * near) / (far - near);
    result.m[14] = -1.0f;
    result.m[15] = 0.0f;
    
    return result;
}

Mat4 Mat4::look_at(const Vec3& eye, const Vec3& target, const Vec3& up) {
    // create view matrix for camera positioning
    Vec3 forward = (target - eye).normalize();
    Vec3 right = forward.cross(up).normalize();
    Vec3 camera_up = right.cross(forward);
    
    Mat4 result;
    result.m[0] = right.x;    result.m[1] = right.y;    result.m[2] = right.z;
    result.m[4] = camera_up.x; result.m[5] = camera_up.y; result.m[6] = camera_up.z;
    result.m[8] = -forward.x; result.m[9] = -forward.y; result.m[10] = -forward.z;
    result.m[3] = -right.dot(eye);
    result.m[7] = -camera_up.dot(eye);
    result.m[11] = forward.dot(eye);
    
    return result;
}
