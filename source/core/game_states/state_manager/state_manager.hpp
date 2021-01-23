#include "../i_game_state.hpp"

class StateManager {
private:
    IGameState* currentState = nullptr;
    IGameState* nextState = nullptr;
    bool _isExiting = false;

public:
    void runState(double deltaTime);
    void goToState(IGameState *nextState);
    void setIsExiting(bool isExiting){_isExiting = isExiting;}
    [[nodiscard]] bool isExiting() const{return _isExiting;}
};