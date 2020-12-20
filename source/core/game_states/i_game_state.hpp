#pragma once

#include "../../graphics/shader/shader.hpp"
#include "../../entity/entity_manager.hpp"
#include "../system/renderSystem.h"



class IGameState{
protected:
    EntityManager entityManager;
    RenderSystem* renderSystem;

public:
    virtual void onEnter() = 0;
    virtual void onDraw(float deltaTime) = 0;
    virtual void onExit() = 0;
};