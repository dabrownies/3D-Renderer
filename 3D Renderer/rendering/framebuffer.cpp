// framebuffer.cpp
// implementation of framebuffer operations and file output
// handles pixel management and depth testing

#include "framebuffer.h"
#include <fstream>
#include <iostream>

Pixel::Pixel() : r(0), g(0), b(0), depth(1.0f) {}

void Pixel::set_color(const Vec3& color) {
    // convert floating point color values to byte range with clamping
    Color::to_bytes(color, r, g, b);
}

Framebuffer::Framebuffer(int w, int h) : width(w), height(h) {
    pixels.resize(width * height);
}

void Framebuffer::clear(const Vec3& color) {
    // clear entire framebuffer to solid color and reset depth buffer
    for (auto& pixel : pixels) {
        pixel.set_color(color);
        pixel.depth = 1.0f;  // far plane in normalized device coordinates
    }
}

void Framebuffer::set_pixel(int x, int y, const Vec3& color, float depth) {
    // set pixel with depth testing (z-buffer algorithm)
    if (x >= 0 && x < width && y >= 0 && y < height) {
        int index = y * width + x;
        
        // only update pixel if this fragment is closer than existing one
        if (depth < pixels[index].depth) {
            pixels[index].set_color(color);
            pixels[index].depth = depth;
        }
    }
}

Vec3 Framebuffer::get_pixel_color(int x, int y) const {
    // read pixel color back as floating point values
    if (x >= 0 && x < width && y >= 0 && y < height) {
        int index = y * width + x;
        const Pixel& p = pixels[index];
        return Vec3(p.r / 255.0f, p.g / 255.0f, p.b / 255.0f);
    }
    return Vec3(0, 0, 0);
}

void Framebuffer::save_ppm(const std::string& filename) const {
    // save framebuffer as ppm image file (simple uncompressed format)
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing" << std::endl;
        return;
    }
    
    // ppm header: format, dimensions, max color value
    file << "P3\n" << width << " " << height << "\n255\n";
    
    // write pixel data row by row
    for (const auto& pixel : pixels) {
        file << (int)pixel.r << " " << (int)pixel.g << " " << (int)pixel.b << "\n";
    }
    
    std::cout << "Image saved as " << filename << std::endl;
}
