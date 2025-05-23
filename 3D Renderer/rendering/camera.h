// camera.h
// camera class for 3d scene viewing and navigation
// handles view transformations and projection settings

#ifndef CAMERA_H
#define CAMERA_H

#include "../math/Vec3.h"
#include "../math/mat4.h"

// camera class for viewing 3d scenes from different perspectives
// provides view matrix generation and basic camera controls
class Camera {
public:
    Vec3 position;      // where the camera is located in world space
    Vec3 target;        // point the camera is looking at
    Vec3 up;           // which direction is "up" for the camera
    float fov;         // field of view angle in radians
    float aspect_ratio; // width/height ratio of the viewport
    float near_plane;   // closest visible distance
    float far_plane;    // furthest visible distance
    
    Camera(const Vec3& pos = Vec3(0, 0, 5),
           const Vec3& tgt = Vec3(0, 0, 0),
           const Vec3& up_vec = Vec3(0, 1, 0),
           float field_of_view = 60.0f,
           float aspect = 16.0f/9.0f);
    
    // matrix generation for rendering pipeline
    Mat4 get_view_matrix() const;        // world-to-camera transformation
    Mat4 get_projection_matrix() const;  // camera-to-screen projection
    
    // basic camera movement controls
    void move_forward(float distance);               // move along view direction
    void move_right(float distance);                 // strafe perpendicular to view
    void rotate_around_target(float angle_x, float angle_y);  // orbital camera rotation
};

#endif
