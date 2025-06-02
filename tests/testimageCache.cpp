#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "imageCache.h"
#include "doctest.h"

std::string imagePath = "../assets/pictures/";
std::vector<std::string> images = {
    "picture1.jpg",
    "picture2.jpg",
    "picture3.jpg",
    "placeholder.jpg"
};

TEST_CASE("ImageCache loads images and retrieves them") {
    ImGui::CreateContext();

    ImageCache imageCache;
    imageCache.loadImages(imagePath, images);

    // Normal getImageData test
    CHECK(imageCache.getImageData("picture1.jpg") != nullptr);

    // Checks persistency after loading image
    // CHECK();

    // Check for a unavailable image
    CHECK(imageCache.getImageData("fakePicture.jpg") == nullptr);

    // Sanity test
    //CHECK(imageCache.getImageData("picture1.jpg") == nullptr);

    ImGui::DestroyContext();
}