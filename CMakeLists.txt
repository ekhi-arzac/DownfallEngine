cmake_minimum_required(VERSION 3.16)
project(DownfallEngine VERSION 1.0.0 LANGUAGES C CXX)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Include FetchContent for downloading dependencies
include(FetchContent)

# Fetch GLM library
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

# Fetch Dear ImGui library
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.89.2
)
FetchContent_MakeAvailable(imgui)

# Create ImGui library manually since it doesn't provide a CMakeLists.txt
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
)

target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC
    glfw
    OpenGL::GL
)

# Include directories for external dependencies
include_directories(${CMAKE_SOURCE_DIR}/external/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/external/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/external/stb/include)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include/*")
foreach(INCLUDE_DIR ${INCLUDE_DIRS})
    if(IS_DIRECTORY ${INCLUDE_DIR})
        include_directories(${INCLUDE_DIR})
    endif()
endforeach()

# Add GLAD source files
set(GLAD_SOURCE "${CMAKE_SOURCE_DIR}/external/glad/src/glad.c")

# Find required packages
find_package(OpenGL REQUIRED)

# Build GLFW from source (if you have the complete source in external/glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw)

# Define executable target and source files
# Replace with your source files
file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Create the executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${GLAD_SOURCE})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    OpenGL::GL
    glm
    ${CMAKE_DL_LIBS}  # Needed for GLAD on some platforms
    imgui
)

# Add platform specific libraries if needed
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE X11 Xrandr Xinerama Xi Xcursor pthread)
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
endif()

# Installation rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Enable all compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()
