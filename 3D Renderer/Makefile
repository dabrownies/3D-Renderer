# Makefile for 3D Rendering Engine
# builds the complete rendering engine from modular source files

# compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I.
TARGET = render_engine

# Source files with folder paths
MATH_SOURCES = math/vec3.cpp math/mat4.cpp
GEOMETRY_SOURCES = geometry/vertex.cpp geometry/triangle.cpp geometry/material.cpp geometry/mesh.cpp
LIGHTING_SOURCES = lighting/light.cpp
RENDERING_SOURCES = rendering/camera.cpp rendering/framebuffer.cpp rendering/renderer.cpp
SCENE_SOURCES = scene/scene.cpp
MAIN_SOURCE = main.cpp

# combine all source files
SOURCES = $(MATH_SOURCES) $(GEOMETRY_SOURCES) $(LIGHTING_SOURCES) $(RENDERING_SOURCES) $(SCENE_SOURCES) $(MAIN_SOURCE)

# object files (replace .cpp with .o)
OBJECTS = $(SOURCES:.cpp=.o)

# build rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "Build complete!"

# compile individual source files
%.o: %.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# run the demo
run: $(TARGET)
	@echo "Running 3D rendering demo..."
	./$(TARGET)

# clean build artifacts
clean:
	@echo "Cleaning build files..."
	rm -f $(OBJECTS) $(TARGET) *.ppm
	@echo "Clean complete!"

# show file structure
info:
	@echo "3D Rendering Engine File Structure:"
	@echo "Math: $(MATH_SOURCES)"
	@echo "Geometry: $(GEOMETRY_SOURCES)"
	@echo "Lighting: $(LIGHTING_SOURCES)"
	@echo "Rendering: $(RENDERING_SOURCES)"
	@echo "Scene: $(SCENE_SOURCES)"
	@echo "Main: $(MAIN_SOURCE)"

.PHONY: all run clean info
