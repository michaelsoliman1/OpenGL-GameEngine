//
// Created by michael on ٢١‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_GUISYSTEM_H
#define GRAPHICS_GUISYSTEM_H

// Include the Dear ImGui implementation headers
#define IMGUI_IMPL_OPENGL_LOADER_GLAD2
#include <imgui_impl/imgui_impl_glfw.h>
#include <imgui_impl/imgui_impl_opengl3.h>

#include <application.hpp>

class EntityManager;

class GUISystem {
public:
    static void initialize(xGame::Application *app);
    static void onUpdateEnter();
    static void update(EntityManager *entityManager,xGame::Application *app);
    static void onUpdateExit(xGame::Application *app);
    static void draw();
    static void destroy();
};


#endif //GRAPHICS_GUISYSTEM_H
