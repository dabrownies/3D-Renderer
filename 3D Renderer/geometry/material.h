// material.h
// material properties for surface appearance
// defines how objects interact with light (phong reflection model)

#ifndef MATERIAL_H
#define MATERIAL_H

#include "../math/Vec3.h"

// material structure defining surface optical properties
// controls how light reflects off surfaces for realistic appearance
struct Material {
    Vec3 diffuse_color;    // base color when illuminated by light
    Vec3 specular_color;   // color of shiny reflective highlights
    float shininess;       // how sharp/tight the specular highlights are (higher = shinier)
    float ambient_strength; // how much ambient light affects this surface
    
    Material(const Vec3& diffuse = Vec3(0.7f, 0.7f, 0.7f),
             const Vec3& specular = Vec3(1, 1, 1),
             float shine = 32.0f,
             float ambient = 0.1f);
};

#endif
