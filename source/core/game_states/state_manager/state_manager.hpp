#include "../i_game_state.hpp"

class StateManager {
private:
    IGameState* currentState;
    IGameState* nextState;
    bool _isExiting = false;

public:
    void runState(double deltaTime);
    void goToState(IGameState *nextState);
    void setIsExiting(bool isExiting){_isExiting = isExiting;}
    bool isExiting(){return _isExiting;}
};