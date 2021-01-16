#pragma once

#include <application.hpp>
#include "i_game_state.hpp"


class TestState : public IGameState {
public:
    TestState(xGame::Application* app) : IGameState(app){};
    ~TestState() = default;

    void onEnter() override;
    void onDraw(float deltaTime) override;
    void onExit() override;
};
