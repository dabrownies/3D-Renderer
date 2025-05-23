// light.cpp
// implementation of light source functionality
// handles different light types and their setup

#include "light.h"

Light::Light(LightType t, const Vec3& pos_or_dir, const Vec3& col, float intens)
    : type(t), color(col), intensity(intens) {
    
    if (t == LightType::POINT) {
        // point light: store position, calculate direction per pixel
        position = pos_or_dir;
    } else {
        // directional light: store normalized direction, no position needed
        direction = pos_or_dir.normalize();
    }
}
