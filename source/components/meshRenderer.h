//
// Created by ecs on 12/6/2020.
//
#include "renderer.hpp"
#include "../graphics/shader.hpp"
#include "../mesh/mesh.hpp"

#ifndef GRAPHICS_MESHRENDERER_H
#define GRAPHICS_MESHRENDERER_H

class MeshRenderer : public Renderer {
public:
    xGame::Mesh *mesh;
    xGame::ShaderProgram *renderShader;

    //i can't understand point 3
};
#endif //GRAPHICS_MESHRENDERER_H
