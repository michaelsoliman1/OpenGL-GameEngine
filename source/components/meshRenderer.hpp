//
// Created by ecs on 12/6/2020.
//
#include "renderer.hpp"
#include "../graphics/shader.hpp"
#include "../mesh/mesh.hpp"

#ifndef GRAPHICS_MESHRENDERER_H
#define GRAPHICS_MESHRENDERER_H

class MeshRenderer : public Renderer {
    xGame::Mesh *mesh;
    xGame::ShaderProgram *renderShader;
public:
    MeshRenderer();

};
#endif //GRAPHICS_MESHRENDERER_H
