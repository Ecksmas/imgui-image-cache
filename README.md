# ImGui Image Cache

A image cache system used with Dear ImGui, which was created for the need to be able to reuse already loaded images and manage memory of them.

## Overview

Dear ImGui offers basic image rendering, but lacks a built-in cache system. Image must be either loaded again and again or risk to leak memory while loading the images.

This project introduces a **image cache system** to centralise image loading and ease of access by retrieving the image data and loading it directly only once.

The project includes:
- A image cache that loads and store image data.
- An interactive demo that lets the user see 4 different pictures where one is a placeholder.
- A clean setup using modern C++17 and CMake.

## Testing

Doctest is used in the testing of the project, some simple test to check that everything is running correctly.

To run tests:
- cd build
- ./runTests

## Purpose

The purpose of creating this code was to create something that can be used when creating ImGui projects that use a lot of different images. Additionally, it was created to demostrate and improve my knowledge of cache systems.

### `ImageCache`
A image cache system:
- Loads images once from a map
- Call upon the image data later on
- Provides a simple API:

```cpp
ImageCache imageCache;
imageCache.loadImages(imagePath, images);
ImageData *image1 = imageCache.getImageData("picture1.jpg");
ImVec2 image1Size = ImVec2(image1->width * imageScale, image1->height * imageScale);
ImGui::Image(image1->textureID, image1Size);
