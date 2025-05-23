// color.h
// color utilities and conversion functions
// handles color representation and conversion between formats

#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"
#include <algorithm>

// utility functions for color operations
namespace Color {
    // clamp color values to valid range [0, 1]
    inline Vec3 clamp(const Vec3& color) {
        return Vec3(
            std::clamp(color.x, 0.0f, 1.0f),
            std::clamp(color.y, 0.0f, 1.0f),
            std::clamp(color.z, 0.0f, 1.0f)
        );
    }
    
    // convert floating point color [0,1] to byte values [0,255]
    inline void to_bytes(const Vec3& color, unsigned char& r, unsigned char& g, unsigned char& b) {
        Vec3 clamped = clamp(color);
        r = (unsigned char)(clamped.x * 255);
        g = (unsigned char)(clamped.y * 255);
        b = (unsigned char)(clamped.z * 255);
    }
    
    // common color constants
    const Vec3 BLACK(0, 0, 0);
    const Vec3 WHITE(1, 1, 1);
    const Vec3 RED(1, 0, 0);
    const Vec3 GREEN(0, 1, 0);
    const Vec3 BLUE(0, 0, 1);
    const Vec3 YELLOW(1, 1, 0);
    const Vec3 CYAN(0, 1, 1);
    const Vec3 MAGENTA(1, 0, 1);
}

#endif
