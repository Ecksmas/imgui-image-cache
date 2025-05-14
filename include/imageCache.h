#pragma once

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

    void loadImages(const std::string &basePath, const std::vector<std::string> imageFiles);
    ImageData* getImageData(const std::string fileName);
    void deleteImageCacheData(const std::string fileName);
    void deleteImageCache();
};
