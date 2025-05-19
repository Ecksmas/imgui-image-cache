#include "imageCache.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

std::string imagePath = "../assets/pictures/";
std::vector<std::string> images = {
    "picture1.jpg",
    "picture2.jpg",
    "picture3.jpg",
    "placeholder.jpg"};

int main(int argc, char const *argv[])
{
    if (!glfwInit())
    {
        std::cout << "GLFW init failed" << std::endl;
        return -1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    int glfwWidth = 1000;
    int glfwHeigth = 400;
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(glfwWidth, glfwHeigth, "imgui-font-manager", NULL, NULL);

    if (!window)
    {
        std::cerr << "GLFW window creation failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoBackground |
                                    ImGuiWindowFlags_NoScrollbar |
                                    ImGuiWindowFlags_NoScrollWithMouse;

    /**
     * Start of example
     */

    ImageCache imageCache;
    imageCache.loadImages(imagePath, images);

        while ((!glfwWindowShouldClose(window)))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(glfwWidth, glfwHeigth));
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        ImGui::Begin("Image Cache Demo", 0, window_flags);

        ImageData *image1 = imageCache.getImageData("picture1.jpg");
        ImVec2 image1Size = ImVec2(image1->width, image1->height);

        ImGui::Image(image1->textureID, image1Size);

        /**
         * End of example
         */

        ImGui::End();

        ImGui::Render();
        int displayW, displayH;
        glfwGetFramebufferSize(window, &displayW, &displayH);
        glViewport(0, 0, displayW, displayH);
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
