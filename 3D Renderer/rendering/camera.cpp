// camera.cpp
// implementation of camera functionality and controls
// provides view matrix generation and movement

#include "camera.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Camera::Camera(const Vec3& pos, const Vec3& tgt, const Vec3& up_vec, float field_of_view, float aspect)
    : position(pos), target(tgt), up(up_vec), aspect_ratio(aspect),
      near_plane(0.1f), far_plane(100.0f) {
    // convert field of view from degrees to radians
    fov = field_of_view * M_PI / 180.0f;
}

Mat4 Camera::get_view_matrix() const {
    // generate view matrix that transforms world coordinates to camera space
    return Mat4::look_at(position, target, up);
}

Mat4 Camera::get_projection_matrix() const {
    // generate perspective projection matrix for realistic depth perception
    return Mat4::perspective(fov, aspect_ratio, near_plane, far_plane);
}

void Camera::move_forward(float distance) {
    // move camera forward/backward along the viewing direction
    // maintains the same look direction by moving both position and target
    Vec3 forward = (target - position).normalize();
    position = position + forward * distance;
    target = target + forward * distance;
}

void Camera::move_right(float distance) {
    // strafe camera left/right perpendicular to viewing direction
    // useful for first-person style movement
    Vec3 forward = (target - position).normalize();
    Vec3 right = forward.cross(up).normalize();
    position = position + right * distance;
    target = target + right * distance;
}

void Camera::rotate_around_target(float angle_x, float angle_y) {
    // orbital camera rotation around the target point
    // useful for examining objects from different angles
    Vec3 offset = position - target;
    float radius = offset.length();
    
    // simple spherical coordinate rotation
    static float current_angle_y = 0;
    current_angle_y += angle_y;
    
    // calculate new camera position using spherical coordinates
    position = target + Vec3(
        radius * std::cos(current_angle_y) * std::cos(angle_x),
        radius * std::sin(angle_x),
        radius * std::sin(current_angle_y) * std::cos(angle_x)
    );
}
