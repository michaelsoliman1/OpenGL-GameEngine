#pragma once

#include <shader.hpp>

class IGameState{
protected:
    our::ShaderProgram program;
    GLuint vertex_array = 0;

public:
    virtual void onEnter() = 0;
    virtual void onDraw(float deltaTime) = 0;
    virtual void onExit() = 0;
};