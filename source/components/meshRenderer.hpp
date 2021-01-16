//
// Created by ecs on 12/6/2020.
//
#ifndef GRAPHICS_MESHRENDERER_H
#define GRAPHICS_MESHRENDERER_H

#include "../graphics/mesh/mesh.hpp"
#include "../graphics/mesh/mesh-utils.hpp"
#include "renderer.hpp"
#include "../graphics/material/material.h"


class MeshRenderer : public Renderer {
public:
    xGame::Mesh *model;
    xGame::Material *material;

    MeshRenderer(xGame::Mesh* _mesh = nullptr,xGame::Material* _material = nullptr){
        _mesh == nullptr ? createDefaultCuboid(true) : model = _mesh;
        _material == nullptr ? material = new xGame::Material() :material = _material;
    }

    xGame::Mesh* createDefaultCuboid(bool coloredFaces){
        model = new xGame::Mesh();
        model->Cuboid(coloredFaces);
        return model;
    };

    ~MeshRenderer(){
        delete model;
        delete material;
    }
};

#endif //GRAPHICS_MESHRENDERER_H
