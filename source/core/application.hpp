#ifndef APPLICATION_H
#define APPLICATION_H

#include <glm/vec2.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>




namespace xGame {

    // This struct handles window attributes: (title, size, isFullscreen).
    struct WindowConfiguration {
        const char* title;
        glm::i16vec2 size;
        bool isFullscreen;
    };

    class Application {
    protected:
        GLFWwindow * window = nullptr;      // Pointer to the window created by GLFW using "glfwCreateWindow()".
        void configureOpenGL();                             // This function sets OpenGL Window Hints in GLFW.
        WindowConfiguration getWindowConfiguration();       // Returns the WindowConfiguration current struct instance.

    public:
        GLFWwindow* init();

        // Class Getters.
        GLFWwindow* getWindow(){ return window; }
        [[nodiscard]] const GLFWwindow* getWindow() const { return window; }

        // Get the size of the frame buffer of the window in pixels.
        glm::ivec2 getFrameBufferSize() {
            glm::ivec2 size;
            glfwGetFramebufferSize(window, &(size.x), &(size.y));
            return size;
        }

        // Get the window size. In most cases, it is equal to the frame buffer size.
        // But on some platforms, the framebuffer size may be different from the window size.
        glm::ivec2 getWindowSize() {
            glm::ivec2 size;
            glfwGetWindowSize(window, &(size.x), &(size.y));
            return size;
        }
    };

}

#endif //APPLICATION_H
