// light.h
// light source definitions for scene illumination
// supports different light types with various properties

#ifndef LIGHT_H
#define LIGHT_H

#include "../math/Vec3.h"

// types of light sources available in the engine
enum class LightType {
    POINT,       // point light with position and falloff
    DIRECTIONAL  // directional light like sunlight (parallel rays)
};

// light source structure for illuminating 3d scenes
// different types have different behaviors and properties
struct Light {
    LightType type;     // determines how the light behaves
    Vec3 position;      // world position (point lights only)
    Vec3 direction;     // light direction (directional lights only)
    Vec3 color;         // light color/tint
    float intensity;    // brightness multiplier
    
    Light(LightType t, const Vec3& pos_or_dir, const Vec3& col = Vec3(1, 1, 1), float intens = 1.0f);
};

#endif
