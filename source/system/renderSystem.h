//
// Created by ecs on 12/6/2020.
//
#ifndef GRAPHICS_RENDERSYSTEM_H
#define GRAPHICS_RENDERSYSTEM_H

#include <vector>
#include "../entity/entity_manager.hpp"
#include "../components/transform.hpp"
#include "../components/meshRenderer.hpp"
#include "../components/camera.h"
#include <../graphics/mesh/common-vertex-attributes.hpp>


class RenderSystem {
    std::vector<Entity*> cachedEntities;
public:
    RenderSystem() = default;
//    static void enableDepthTesting();
    static void initialize(EntityManager *entityManager);
    static void draw(EntityManager *entityManager);
    static void destroy(EntityManager *entityManager);
};

#endif //GRAPHICS_RENDERSYSTEM_H
