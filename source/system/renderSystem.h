//
// Created by ecs on 12/6/2020.
//
#include "../entity/entity_manager.hpp"
#ifndef GRAPHICS_RENDERSYSTEM_H
#define GRAPHICS_RENDERSYSTEM_H


class RenderSystem {
public:
    RenderSystem();
    void initialize(Entity* entity);
    void draw(Entity* entity);
    void destroy(Entity* entity);
};

#endif //GRAPHICS_RENDERSYSTEM_H
