#include "application.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

// Include the Dear ImGui implementation headers
#define IMGUI_IMPL_OPENGL_LOADER_GLAD2
#include <imgui_impl/imgui_impl_glfw.h>
#include <imgui_impl/imgui_impl_opengl3.h>

#if !defined(NDEBUG)
// If NDEBUG (no debug) is not defined, enable OpenGL debug messages
#define ENABLE_OPENGL_DEBUG_MESSAGES
#endif

// This function will be used to log errors thrown by GLFW
void glfw_error_callback(int error, const char* description){
    std::cerr << "GLFW Error: " << error << ": " << description << std::endl;
}

// This function will be used to log OpenGL debug messages
void GLAPIENTRY opengl_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::string _source;
    std::string _type;
    std::string _severity;

    // What is the source of the message
    switch (source) {
        case GL_DEBUG_SOURCE_API:
            _source = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            _source = "WINDOW SYSTEM"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            _source = "SHADER COMPILER"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            _source = "THIRD PARTY"; break;
        case GL_DEBUG_SOURCE_APPLICATION:
            _source = "APPLICATION"; break;
        case GL_DEBUG_SOURCE_OTHER: default:
            _source = "UNKNOWN"; break;
    }

    // What is the type of the message (error, warning, etc).
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            _type = "ERROR"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            _type = "DEPRECATED BEHAVIOR"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            _type = "UDEFINED BEHAVIOR"; break;
        case GL_DEBUG_TYPE_PORTABILITY:
            _type = "PORTABILITY"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            _type = "PERFORMANCE"; break;
        case GL_DEBUG_TYPE_OTHER:
            _type = "OTHER"; break;
        case GL_DEBUG_TYPE_MARKER:
            _type = "MARKER"; break;
        default:
            _type = "UNKNOWN"; break;
    }

    // How severe is the message
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            _severity = "HIGH"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            _severity = "MEDIUM"; break;
        case GL_DEBUG_SEVERITY_LOW:
            _severity = "LOW"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            _severity = "NOTIFICATION"; break;
        default:
            _severity = "UNKNOWN"; break;
    }

    std::cout << "OpenGL Debug Message " << id << " (type: " << _type << ") of " << _severity
    << " raised from " << _source << ": " << message << std::endl;
}

void xGame::Application::configureOpenGL() {
    // Request that OpenGL is 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Only enable core functionalities (disable features from older OpenGL versions that were removed in 3.3)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Enable forward compatibility with newer OpenGL versions by removing deprecated functionalities
    // This is necessary for some platforms
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //Make window size fixed (User can't resize it)
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    //Set Number of sample used in MSAA (0 = Disabled)
    glfwWindowHint(GLFW_SAMPLES, 0);

    //Enable Double Buffering
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    //Set the bit-depths of the frame buffer
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);

    //Set Bits for Depth Buffer
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    //Set Bits for Stencil Buffer
    glfwWindowHint(GLFW_STENCIL_BITS, 8);

    //Set the refresh rate of the window (GLFW_DONT_CARE = Run as fast as possible)
    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
}

xGame::WindowConfiguration xGame::Application::getWindowConfiguration() {
    return {"OpenGL Application", {1280, 720}, false };
}

GLFWwindow* xGame::Application::initWindow() {

    // Set the function to call when an error occurs.
    glfwSetErrorCallback(glfw_error_callback);

    // Initialize GLFW and exit if it failed
    if (!glfwInit()) {
        std::cerr << "Failed to Initialize GLFW" << std::endl;
        return nullptr;
    }

    configureOpenGL();                                      // This function sets OpenGL window hints.

    auto win_config = getWindowConfiguration();             // Returns the WindowConfiguration current struct instance.


    // Create a window with the given "WindowConfiguration" attributes.
    // If it should be fullscreen, monitor should point to one of the monitors (e.g. primary monitor), otherwise it should be null
    GLFWmonitor *monitor = win_config.isFullscreen ? glfwGetPrimaryMonitor() : nullptr;
    // The last parameter "share" can be used to share the resources (OpenGL objects) between multiple windows.
    window = glfwCreateWindow(win_config.size.x, win_config.size.y, win_config.title, monitor, nullptr);
    if (!window) {
        std::cerr << "Failed to Create Window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);         // Tell GLFW to make the context of our window the main context on the current thread.

    gladLoadGL(glfwGetProcAddress);         // Load the OpenGL functions from the driver

    // Print information about the OpenGL context
    std::cout << "VENDOR          : " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "RENDERER        : " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "VERSION         : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL VERSION    : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

#if defined(ENABLE_OPENGL_DEBUG_MESSAGES)
    // if we have OpenGL debug messages enabled, set the message callback
    glDebugMessageCallback(opengl_callback, nullptr);
    // Then enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    // Then make the output synchronized to the OpenGL commands.
    // This will make sure that OpenGL and the main thread are synchronized such that message callback is called as soon
    // as the command causing it is called. This is useful for debugging but slows down the code execution.
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif

    setupCallbacks();
    keyboard.enable(window);
    mouse.enable(window);


    return window;
}


void xGame::Application::setupCallbacks() {

    // We use GLFW to store a pointer to "this" window instance.
    glfwSetWindowUserPointer(window, this);
    // The pointer is then retrieved in the callback function.

    // The second parameter to "glfwSet---Callback" is a function pointer.
    // It is replaced by an inline function -lambda expression- as it is not needed to create
    // a seperate function for it.
    // In the inline function we retrieve the window instance and use it to set our (Mouse/Keyboard) classes values.

    // Keyboard callbacks
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
        auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if(app){
            app->eventManager->keyboardEvents.notifyListeners(key, scancode, action, mods);
            app->getKeyboard().keyEvent(key, scancode, action, mods);
        }
    });

    // mouse position callbacks
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x_position, double y_position){
        auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if(app){
            app->eventManager->mousePositionEvents.notifyListeners(x_position, y_position);
            app->getMouse().CursorMoveEvent(x_position, y_position);
        }
    });

    // mouse position callbacks
    glfwSetCursorEnterCallback(window, [](GLFWwindow* window, int entered){
        auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if(app){
        }
    });

    // mouse button position callbacks
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods){
        auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if(app){
            app->eventManager->mouseButtonEvents.notifyListeners(button, action, mods);
            app->getMouse().MouseButtonEvent(button, action, mods);
        }
    });

    // mouse scroll callbacks
    glfwSetScrollCallback(window, [](GLFWwindow* window, double x_offset, double y_offset){
        auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if(app){
            app->eventManager->mouseScrollEvents.notifyListeners(x_offset,y_offset);
            app->getMouse().ScrollEvent(x_offset, y_offset);
        }
    });
}