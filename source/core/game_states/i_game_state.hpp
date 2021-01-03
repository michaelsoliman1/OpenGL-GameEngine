#pragma once

#include "../../graphics/shader/shader.hpp"
#include "../../entity/entity_manager.hpp"
#include "../system/render_system.h"
#include "../system/camera_system.h"





class IGameState{
protected:
    EntityManager* entityManager;
    RenderSystem* renderSystem;
    CameraSystem* cameraSystem;
//    GLFWwindow* window = nullptr;

public:
    IGameState(){
//        this->window = window;
        //question: should we allocate the pointers here ? or in onEnter()?
        entityManager = new EntityManager();
        renderSystem = new RenderSystem();
        cameraSystem = new CameraSystem();
    }

    ~IGameState(){
//        delete this->window;
        delete this->entityManager;
        delete this->renderSystem;
    }

    virtual void onEnter(xGame::Application*) = 0;
    virtual void onDraw(float deltaTime) = 0;
    virtual void onExit() = 0;
};