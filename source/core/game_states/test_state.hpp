#pragma once

#include "i_game_state.hpp"


class TestState : public IGameState {
public:
    TestState() = default;
    virtual ~TestState() = default;

    void onEnter() override;
    void onDraw(float deltaTime) override;
    void onExit() override;
};
