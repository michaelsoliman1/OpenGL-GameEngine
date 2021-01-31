#ifndef APPLICATION_H
#define APPLICATION_H

#include <utility>
#include <glm/vec2.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "../input/keyboard.hpp"
#include "../input/mouse.hpp"
#include "../events/event_manager.h"


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
        EventManager* eventManager;

        static void configureOpenGL();                             // This function sets OpenGL Window Hints in GLFW.
        static WindowConfiguration getWindowConfiguration();       // Returns the WindowConfiguration current struct instance.
        void setupCallbacks();                              // Sets-up the window callback functions from GLFW to our (Mouse/Keyboard) classes.

    public:
        explicit Application(EventManager* _eventManager){
            eventManager = _eventManager;
        }
        GLFWwindow* initWindow();

        // Class Getters.
        GLFWwindow* getWindow(){ return window; }
        [[nodiscard]] const GLFWwindow* getWindow() const { return window; }
        Keyboard& getKeyboard() { return keyboard; }
        [[nodiscard]] const Keyboard& getKeyboard() const { return keyboard; }
        Mouse& getMouse() { return mouse; }
        [[nodiscard]] const Mouse& getMouse() const { return mouse; }
        EventManager* getEventManager() { return eventManager; }

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

        void imGuiWantCapture(){
            keyboard.setEnabled(!ImGui::GetIO().WantCaptureKeyboard, window);
            mouse.setEnabled(!ImGui::GetIO().WantCaptureMouse, window);
        }
    };

}

#endif //APPLICATION_H
