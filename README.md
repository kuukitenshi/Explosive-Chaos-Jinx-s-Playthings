# Explosive Chaos: Jinx’s Playthings

## Project Overview

This project showcases a dynamic 3D scene using OpenGL, inspired by Jinx from *Arcane*, highlighting her explosive personality and unique "toys." The scene implements advanced lighting models, texture mapping techniques, and efficient scene management to create a visually captivating environment.

## Key Features

### **Lighting Models**

- **Blinn-Phong Lighting Model:** Achieves realistic illumination by combining ambient, diffuse, and specular components. It uses a half-vector for realistic highlights and light attenuation to enhance distance perception.
- **Cel Shading:** Provides a sketchy, stylized appearance to key objects such as the Hextech crystal. Colors are assigned based on discrete intensity thresholds, creating a dark silhouette through:
  - A second render pass with expanded normals and front-face culling.
  - Rim lighting to emphasize glowing edges, mirroring the *Arcane* aesthetic.

### **Texture Mapping**

- **Normal Mapping:** Enhances surface details by simulating depth and intricate textures, such as metal roughness and engravings. RGB normal maps are used to modify light interactions.
- **Procedural Texture Generation:**
  - **Wood:** Smooth noise with linear interpolations for realistic grain patterns.
  - **Marble & Brick:** Rougher noise with multi-octave accumulation using cubic interpolations. Gradients are mapped to grayscale pixel values and converted to realistic colors.

### **Scene Graph Management**

Efficient handling of transformations, shaders, hierarchical relationships, and other elements is managed through a scene graph, ensuring smooth scene complexity management.

---

## Project Structure

```plaintext
.
├── code/
│   └── source/ (Build instructions in build.txt)
├── engine/ (Engine code and dependencies)
├── media/
│   ├── docs/ (User manual with available options)
│   ├── report/ (Detailed report on techniques and implementation)
│   ├── snapshots/ (Scene images)
│   └── videos/ (Scene demonstration videos)
└── README.md
```

## Build Instructions

To build and run the project, navigate to the `code/source` directory and follow the instructions in `build.txt`.

## Dependencies

   - **CMake (>= 3.26)**
   - **C++20 compatible compiler**
   - **GLM:** Math library
   - **GLAD:** OpenGL bindings
   - **GLFW:** Windowing system
   - **ASSIMP:** Model loading library


## Documentation

- **User Manual:** Located in `media/docs`, detailing available options and usage instructions.
- **Technical Report:** Detailed explanations of techniques and implementation in `media/report`.
- **Snapshots:** Screenshots of the 3D scene can be found in `media/snapshots`.
- **Videos:** Demonstration videos of the scene are available in `media/videos`.

## Conclusion

This project combines advanced rendering techniques and efficient scene management to create a visually stunning and immersive 3D environment inspired by *Arcane*. Explore the intricate details, vibrant textures, and explosive personality embodied in this scene.