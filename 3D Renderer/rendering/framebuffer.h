// framebuffer.h
// framebuffer management for pixel rendering and output
// handles pixel storage, depth testing, and image file output

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "../math/Vec3.h"
#include "../math/color.h"
#include <vector>
#include <string>

// pixel structure containing color and depth information
struct Pixel {
    unsigned char r, g, b;  // rgb color values (0-255)
    float depth;            // z-buffer depth for hidden surface removal
    
    Pixel();
    void set_color(const Vec3& color);  // convert float color to bytes
};

// framebuffer class for managing the rendered image
// provides pixel operations, depth testing, and file output
class Framebuffer {
private:
    int width, height;
    std::vector<Pixel> pixels;  // 2d pixel array stored as 1d vector
    
public:
    Framebuffer(int w, int h);
    
    // framebuffer operations
    void clear(const Vec3& color = Vec3(0, 0, 0));           // clear to solid color
    void set_pixel(int x, int y, const Vec3& color, float depth = 0.0f);  // set single pixel with depth test
    Vec3 get_pixel_color(int x, int y) const;               // read pixel color
    
    // accessor methods
    int get_width() const { return width; }
    int get_height() const { return height; }
    
    // file output
    void save_ppm(const std::string& filename) const;       // save as ppm image file
};

#endif
