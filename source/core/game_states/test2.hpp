#include "i_game_state.hpp"

class TestState2 : public IGameState {
public:
    TestState2() = default;
    virtual ~TestState2() = default;

    void onEnter() override;
    void onDraw(float deltaTime) override;
    void onExit() override;
};
