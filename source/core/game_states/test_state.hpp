#pragma once

#include <application.hpp>
#include "i_game_state.hpp"


class TestState : public IGameState {
public:
    TestState() = default;
    ~TestState() = default;

    void onEnter(xGame::Application*) override;
    void onDraw(float deltaTime) override;
    void onExit() override;
};
