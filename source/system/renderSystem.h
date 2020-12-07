//
// Created by ecs on 12/6/2020.
//
#include "../components/renderer.hpp"
//#include "../entity/entity.hpp"
#include "../entity/entity_manager.hpp"
#ifndef GRAPHICS_RENDERSYSTEM_H
#define GRAPHICS_RENDERSYSTEM_H
class RenderSystem {
public:
    RenderSystem();
    Renderer render(EntityManager entityList, IComponent* component);
};
#endif //GRAPHICS_RENDERSYSTEM_H
