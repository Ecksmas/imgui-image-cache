#pragma once

#include <string>
#include <map>
#include <vector>
#include <imgui.h>
#include <GLFW/glfw3.h>

// typedef unsigned int GLuint;

// Not yet implemented
enum class ImageCacheReturnStatus {
    None,
    Success,
    NotFound,
    UnknownError
};

struct ImageData
{
    GLuint textureID;
    int width;
    int height;
};

class ImageCache
{
private:
    std::map<std::string, ImageData> mImageCache;
    const std::string mFallBackImage = "placeholder.jpg";

public:
    ~ImageCache();

    void loadImages(const std::string &path, const std::vector<std::string> imageFiles);
    ImageData* getImageData(const std::string &fileName);
    int trackMemoryUsage();
    void deleteImageCache();
};
