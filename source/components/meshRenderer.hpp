//
// Created by ecs on 12/6/2020.
//
#ifndef GRAPHICS_MESHRENDERER_H
#define GRAPHICS_MESHRENDERER_H

#include "../graphics/mesh/mesh.hpp"
#include "../graphics/mesh/mesh-utils.hpp"
#include "renderer.hpp"
#include "../graphics/material/material.h"

enum MeshType{
    Cuboid,
};

class MeshRenderer : public Renderer {
public:
    MeshRenderer(){
        model = new xGame::Mesh();
        material = new xGame::Material();
    };

    MeshRenderer(xGame::Material* _material){
        model = new xGame::Mesh();
        material = _material;
    }

    void createCuboid(bool coloredFaces){
        xGame::mesh_utils::Cuboid(*model, coloredFaces);
    };
    void createPlane(){
        xGame::mesh_utils::Plane(*model, {1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});;
    }

    xGame::Mesh *model;
    xGame::Material *material;


};

#endif //GRAPHICS_MESHRENDERER_H
