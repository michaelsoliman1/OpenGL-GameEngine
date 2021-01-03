#include "state_manager.hpp"

void StateManager::runState(double deltaTime, xGame::Application* app) {
    if(!_isExiting){
        if(nextState!= nullptr){
            if(currentState!= nullptr){
                currentState->onExit();
            }
            currentState= nextState;
            nextState = nullptr;
            currentState->onEnter(app);
        }
        if(currentState!= nullptr){
            currentState->onDraw(deltaTime);
        }
    } else {
        if(currentState!= nullptr){
            currentState->onExit();
        }
    };

}

void StateManager::goToState(IGameState *nextState) {
    this->nextState = nextState;
}
