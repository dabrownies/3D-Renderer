// material.cpp
// implementation of material properties
// constructor for phong reflection model parameters

#include "material.h"

Material::Material(const Vec3& diffuse, const Vec3& specular, float shine, float ambient)
    : diffuse_color(diffuse), specular_color(specular), shininess(shine), ambient_strength(ambient) {
}
