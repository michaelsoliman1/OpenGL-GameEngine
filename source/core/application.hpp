#ifndef APPLICATION_H
#define APPLICATION_H

#include <glm/vec2.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "../input/keyboard.hpp"
#include "../input/mouse.hpp"




namespace xGame {

    // This struct handles window attributes: (title, size, isFullscreen).
    struct WindowConfiguration {
        const char* title;
        glm::i16vec2 size;
        bool isFullscreen;
    };

    class Application {
        GLFWwindow * window = nullptr;      // Pointer to the window created by GLFW using "glfwCreateWindow()".

        Keyboard keyboard;
        Mouse mouse;

        void configureOpenGL();                             // This function sets OpenGL Window Hints in GLFW.
        WindowConfiguration getWindowConfiguration();       // Returns the WindowConfiguration current struct instance.
        void setupCallbacks();                              // Sets-up the window callback functions from GLFW to our (Mouse/Keyboard) classes.

    public:
        GLFWwindow* initWindow();

        // Class Getters.
        GLFWwindow* getWindow(){ return window; }
        [[nodiscard]] const GLFWwindow* getWindow() const { return window; }
        Keyboard& getKeyboard() { return keyboard; }
        [[nodiscard]] const Keyboard& getKeyboard() const { return keyboard; }
        Mouse& getMouse() { return mouse; }
        [[nodiscard]] const Mouse& getMouse() const { return mouse; }

        void onKeyEvent(int key, int scancode, int action, int mods){}
        void onCursorMoveEvent(double x, double y){}
        void onCursorEnterEvent(int entered){}
        void onMouseButtonEvent(int button, int action, int mods){}
        void onScrollEvent(double x_offset, double y_offset){}

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
