//
// Created by ecs on 12/6/2020.
//
#ifndef GRAPHICS_MESHRENDERER_H
#define GRAPHICS_MESHRENDERER_H

#include "../graphics/shader/shader.hpp"
#include "../graphics/mesh/mesh.hpp"
#include "renderer.hpp"



class MeshRenderer : public Renderer {
public:
    MeshRenderer(){
        quad = new xGame::Mesh();
        program = new xGame::ShaderProgram();
    };

    xGame::Mesh *quad;
    xGame::ShaderProgram *program;
    glm::vec4 tint = glm::vec4(1,1,1,1);
};

#endif //GRAPHICS_MESHRENDERER_H
