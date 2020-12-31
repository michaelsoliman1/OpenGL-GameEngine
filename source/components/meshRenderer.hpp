//
// Created by ecs on 12/6/2020.
//
#ifndef GRAPHICS_MESHRENDERER_H
#define GRAPHICS_MESHRENDERER_H

#include "../graphics/shader/shader.hpp"
#include "../graphics/mesh/mesh.hpp"
#include "../graphics/mesh/mesh-utils.hpp"

#include "renderer.hpp"



class MeshRenderer : public Renderer {
public:
    MeshRenderer(){
        model = new xGame::Mesh();
        program = new xGame::ShaderProgram();
    };

    void createCuboid(bool coloredFaces){
        xGame::mesh_utils::Cuboid(*model, coloredFaces);
    };

    xGame::Mesh *model;
    xGame::ShaderProgram *program;
    glm::vec4 tint = glm::vec4(1,1,1,1);
};

#endif //GRAPHICS_MESHRENDERER_H
