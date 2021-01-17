#pragma once

#include <application.hpp>
#include "i_game_state.hpp"
#include "../system/render_system/render_system.h"
#include "../system/camera_system/camera_system.h"
#include "../system/movement_system/movement_system.h"

class TestState : public IGameState {
public:
    explicit TestState(xGame::Application* app) : IGameState(app){};
    ~TestState() = default;

    void onEnter() override;
    void onDraw(float deltaTime) override;
    void onExit() override;
};
