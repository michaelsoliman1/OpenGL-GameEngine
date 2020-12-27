//
// Created by ecs on 12/6/2020.
//
#include "../entity/entity_manager.hpp"
#ifndef GRAPHICS_RENDERSYSTEM_H
#define GRAPHICS_RENDERSYSTEM_H


class RenderSystem {
public:
    RenderSystem();
    void initialize(EntityManager *entityManager);
    void draw(EntityManager *entityManager);
    void destroy(EntityManager *entityManager);
};

#endif //GRAPHICS_RENDERSYSTEM_H
