#include "state_manager.hpp"

void StateManager::runState(double deltaTime) {
    if(!_isExiting){
        if(nextState!= nullptr){
            if(currentState!= nullptr){
                currentState->onExit();
            }
            currentState= nextState;
            nextState = nullptr;
            currentState->onEnter();
        }
        if(currentState!= nullptr){
            currentState->onImmediateGui();
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

