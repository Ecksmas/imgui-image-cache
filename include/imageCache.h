#pragma once

#include <string>
#include <map>
#include <vector>
#include <imgui.h>

typedef unsigned int GLuint;

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

public:
    ~ImageCache();

    void loadImages(const std::string &path, const std::vector<std::string> imageFiles);
    ImageData* getImageData(const std::string &fileName);
    void trackMemoryUsage();
    void statisticsAboutUsage();
    void deleteImageCacheData(const std::string &fileName);
    void deleteImageCache();
};
