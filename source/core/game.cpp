#include <sstream>
#include <ctime>
#include <iomanip>
#include "application.hpp"
#include "game_states/test_state.hpp"
#include "game_states/state_manager/state_manager.hpp"
#include "../utils/screenshot/screenshot.h"
//phase3


int main() {
    xGame::Application app;
    GLFWwindow* window = app.initWindow();
    xGame::Keyboard &keyboard = app.getKeyboard();
    xGame::Mouse &mouse = app.getMouse();


    auto* testState = new TestState(&app);

    auto* stateManager = new StateManager();
    stateManager->goToState(testState);

    double last_frame_time = glfwGetTime();
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents(); // Read all the user events and call relevant callbacks.

        // Get the current time (the time at which we are starting the current frame).
        double current_frame_time = glfwGetTime();

        stateManager->runState(current_frame_time - last_frame_time);

        // Then update the last frame start time (this frame is now the last frame)
        last_frame_time = current_frame_time;

        auto frame_buffer_size = app.getFrameBufferSize();
        glViewport(0, 0, frame_buffer_size.x, frame_buffer_size.y);

        // If F12 is pressed, take a screenshot
        if(keyboard.justPressed(GLFW_KEY_F12)){
            glViewport(0, 0, frame_buffer_size.x, frame_buffer_size.y);
            std::stringstream stream;
            auto time = std::time(nullptr);
            auto localtime = std::localtime(&time);
            stream << "screenshots/screenshot-" << std::put_time(localtime, "%Y-%m-%d-%H-%M-%S") << ".png";
            if(xGame::screenshot_png(stream.str())){
                std::cout << "Screenshot saved to: " << stream.str() << std::endl;
            } else {
                std::cerr << "Failed to save a Screenshot" << std::endl;
            }
        }

        // Swap the frame buffers
        glfwSwapBuffers(window);

        keyboard.update();
        mouse.update();
    }

    stateManager->setIsExiting(true);
    // Destroy the window
    glfwDestroyWindow(window);

    // And finally terminate GLFW
    glfwTerminate();
}