cmake_minimum_required(VERSION 3.0.0)   # Selects the minimum version of CMake required to run this file
project(GRAPHICS VERSION 0.1.0)          # Here we select the project name and version

# Here we select C++17 with all the standards required and all compiler-specific extensions disabled
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# These are the options we select for building GLFW as a library
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)        # Don't build Documentation
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)       # Don't build Tests
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)    # Don't build Examples
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)           # Don't build Installation Information
set(GLFW_USE_HYBRID_HPG ON CACHE BOOL "" FORCE)     # Add variables to use High Performance Graphics Card if available
add_subdirectory(vendor/glfw)                       # Build the GLFW project to use later as a library

# A variable with all the source files of GLAD
set(GLAD_SOURCE vendor/glad/src/gl.c)
# A variables with all the source files of Dear ImGui
set(IMGUI_SOURCES
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_demo.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_widgets.cpp
        vendor/imgui/imgui_impl/imgui_impl_glfw.cpp
        vendor/imgui/imgui_impl/imgui_impl_opengl3.cpp
        )

# Combine all vendor source files together into a single variable
set(VENDOR_SOURCES ${GLAD_SOURCE} ${IMGUI_SOURCES})

# A variable with all our source files that are common between executable targets (examples)
set(COMMON_SOURCES
        source/core/application.cpp
        source/core/game_states/test_state.cpp
        source/core/game_states/state_manager/state_manager.cpp
        source/entity/entity.cpp
        source/entity/entity_manager.cpp
        source/system/camera_system.cpp
        source/system/render_system.cpp
        )
set(RENDERING
        source/graphics/shader/shader.cpp
        source/graphics/mesh/mesh-utils.cpp
        source/graphics/material/material.cpp
        source/graphics/texture/texture.cpp
        source/graphics/sampler/sampler.cpp
        source/graphics/render_state/RenderState.cpp
        source/events/event.cpp source/events/event.h source/core/resources.cpp source/graphics/mesh/mesh.cpp)

# Define the directories in which to search for the included headers
include_directories(
        source/core
        vendor/glfw/include
        vendor/glad/include
        vendor/glm
        vendor/imgui
        vendor/utils
)

# For each example, we add an executable target
# Each target compiles one example source file and the common & vendor source files
# Then we link GLFW with each target

add_executable(Game source/core/game.cpp ${COMMON_SOURCES} ${VENDOR_SOURCES} ${RENDERING})
target_link_libraries(Game glfw)

