//
// Created by michael on ٢١‏/١‏/٢٠٢١.
//
#include "gui_system.h"

void GUISystem::initialize(xGame::Application *app) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    app->setImGuiIO(ImGui::GetIO());
    ImGui::StyleColorsLight();

    // Initialize ImGui for GLFW and OpenGL
    ImGui_ImplGlfw_InitForOpenGL(app->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void GUISystem::onUpdateEnter() {
    // Start a new ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUISystem::update(EntityManager *entityManager, xGame::Application *app) {
    ImGui::Begin("Lights");
    ImGui::End();
}

void GUISystem::onUpdateExit(xGame::Application *app) {
    // If ImGui is using the mouse or keyboard, then we don't want the captured events to affect our keyboard and mouse objects.
    // For example, if you're focusing on an input and writing "W", the keyboard object shouldn't record this event.
    // TODO move all that to a function in app
    app->getKeyboard().setEnabled(!app->getImGuiIO().WantCaptureKeyboard, app->getWindow());
    app->getMouse().setEnabled(!app->getImGuiIO().WantCaptureMouse, app->getWindow());

    // Render the ImGui commands we called (this doesn't actually draw to the screen yet.
    ImGui::Render();

    // Just in case ImGui changed the OpenGL viewport (the portion of the window to which we render the geometry),
    // we set it back to cover the whole window
    auto frame_buffer_size = app->getFrameBufferSize();
    glViewport(0, 0, frame_buffer_size.x, frame_buffer_size.y);
}

void GUISystem::draw() {
#if defined(ENABLE_OPENGL_DEBUG_MESSAGES)
    // Since ImGui causes many messages to be thrown, we are temporarily disabling the debug messages till we render the ImGui
            glDisable(GL_DEBUG_OUTPUT);
            glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Render the ImGui to the framebuffer
#if defined(ENABLE_OPENGL_DEBUG_MESSAGES)
    // Re-enable the debug messages
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif
}

void GUISystem::destroy() {
    // Shutdown ImGui & destroy the context
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

}
