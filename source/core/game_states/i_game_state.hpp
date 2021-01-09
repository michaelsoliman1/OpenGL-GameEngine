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
    xGame::Application* app;

public:
    IGameState(xGame::Application* application){
        app = application;
    }

    ~IGameState(){
        delete this->entityManager;
        delete this->renderSystem;
        delete this->cameraSystem;
    }

    virtual void onEnter() = 0;
    virtual void onDraw(float deltaTime) = 0;
    virtual void onExit() = 0;
};