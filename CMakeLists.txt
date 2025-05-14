cmake_minimum_required(VERSION 3.16)
project(imgui-image-cache)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(IMGUI_SRC
    third_party/imgui/imgui.cpp
    third_party/imgui/imgui_draw.cpp
    third_party/imgui/imgui_tables.cpp
    third_party/imgui/imgui_widgets.cpp
)

# Add ImGui backend files
set(IMGUI_BACKENDS
    third_party/imgui/backends/imgui_impl_glfw.cpp
    third_party/imgui/backends/imgui_impl_opengl3.cpp
)

add_executable(${PROJECT_NAME}
    src/imageCache.cpp
    examples/examplesImageCache.cpp
    ${IMGUI_SRC}
    ${IMGUI_BACKENDS}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/imgui
    ${CMAKE_SOURCE_DIR}/third_party/imgui/backends
)

# Test setup
add_executable(runTests
    tests/testimageCache.cpp
    src/imageCache.cpp
    ${IMGUI_SRC}
)

target_include_directories(runTests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/doctest
    ${CMAKE_SOURCE_DIR}/third_party/imgui
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    glfw
)