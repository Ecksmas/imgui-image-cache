#include "imageCache.h"

#include <iostream>
#include <vector>
#include <map>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Simple helper function to load an image into a OpenGL texture with common settings
bool loadTextureFromMemory(const void *data, size_t data_size, GLuint *out_texture, int *out_width, int *out_height)
{
    int image_width = 0;
    int image_height = 0;

    unsigned char *image_data = stbi_load_from_memory((const unsigned char *)data, (int)data_size, &image_width, &image_height, nullptr, 4);
    if (image_data == nullptr)
    {
        std::cerr << stbi_failure_reason() << std::endl;
        return false;
    }

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

// Open and read a file, then forward to LoadTextureFromMemory()
bool loadTextureFromFile(const char *file_name, GLuint *out_texture, int *out_width, int *out_height)
{
    FILE *f = fopen(file_name, "rb");
    if (f == NULL)
        return false;
    fseek(f, 0, SEEK_END);
    size_t file_size = (size_t)ftell(f);
    if (file_size == -1)
        return false;
    fseek(f, 0, SEEK_SET);
    void *file_data = IM_ALLOC(file_size);
    fread(file_data, 1, file_size, f);
    fclose(f);
    bool ret = loadTextureFromMemory(file_data, file_size, out_texture, out_width, out_height);
    IM_FREE(file_data);
    return ret;
}

// Stores and loads images into the mImageCache map
void ImageCache::loadImages(const std::string &path, const std::vector<std::string> imageFiles)
{
    // Loads in images
    for (const auto &image : imageFiles)
    {
        ImageData imageData;
        bool retExtra = loadTextureFromFile((path + image).c_str(), &imageData.textureID, &imageData.width, &imageData.height);
        std::cout << (path + image) << std::endl;
        IM_ASSERT(retExtra);
        mImageCache.emplace(image, imageData);
    }
}

// Retrives that data from the mImageCache map
ImageData *ImageCache::getImageData(const std::string &fileName)
{
    // Locates the data
    auto it = mImageCache.find(fileName);

    // Locates the placeholder if the requested file is not found
    if (it == mImageCache.end())
    {
        it = mImageCache.find(mFallBackImage);
    }

    // Returns the data depending on the result above
    if (it != mImageCache.end())
    {
        return &it->second;
    }

    std::cerr << "Could not get data or " << mFallBackImage << " in mImageCache" << std::endl;
    return nullptr;
}

// Track the total size of the cache assuming 4 bytes per pixel
int ImageCache::trackMemoryUsage()
{
    int totalBytes = 0;

    for (const auto &pair : mImageCache)
    {
        const ImageData &data = pair.second;
        totalBytes += data.width * data.height * 4;
    }

    return totalBytes;
}

// Clears the whole mImageCache map and set the size of the container to 0
void ImageCache::deleteImageCache()
{
    mImageCache.clear();
}

// Destructor
ImageCache::~ImageCache()
{
    for (const auto &imageData : mImageCache)
    {
        glDeleteTextures(1, &imageData.second.textureID);
    }
    mImageCache.clear();
}