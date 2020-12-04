#include "application.hpp"
#include "game_states/test_state.hpp"
#include "game_states/state_manager/state_manager.hpp"

int main() {
    xGame::Application config;
    GLFWwindow* window = config.init();
    TestState* testState = new TestState();

    StateManager* stateManager = new StateManager();
    stateManager->goToState(testState);

//    testState->onEnter();

    double last_frame_time = glfwGetTime();
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents(); // Read all the user events and call relevant callbacks.

        // Get the current time (the time at which we are starting the current frame).
        double current_frame_time = glfwGetTime();

        stateManager->runState(current_frame_time - last_frame_time);

        // Then update the last frame start time (this frame is now the last frame)
        last_frame_time = current_frame_time;

        // Swap the frame buffers
        glfwSwapBuffers(window);
    }

    stateManager->setIsExiting(true);
    // Destroy the window
    glfwDestroyWindow(window);

    // And finally terminate GLFW
    glfwTerminate();
}