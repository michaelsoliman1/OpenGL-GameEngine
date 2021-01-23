#pragma once

#include <application.hpp>
#include "i_game_state.hpp"
#include "../system/render_system/render_system.h"
#include "../system/camera_system/camera_system.h"
#include "../system/movement_system/movement_system.h"
#include "../system/collision_system/collision_system.h"
#include "../system/gui_system/gui_system.h"


class TestState : public IGameState {
    MovementSystem* movementSystem = nullptr;
public:
    explicit TestState(xGame::Application* app) : IGameState(app){};
    ~TestState() = default;

    void onEnter() override;
    void onImmediateGui() override;
    void onDraw(float deltaTime) override;
    void onExit() override;
};
