//
// Created by ecs on 12/6/2020.
//
#include "renderSystem.h"
#include "../components/renderer.hpp"
#include "../components/transform.hpp"
#include <vector>

RenderSystem::RenderSystem() {};

void RenderSystem::render(EntityManager entityManager, IComponent* component) {
    std::vector<Entity*> entities = entityList.getEntities();
    for (auto&  entity : entities) {
        std::vector<IComponent*> components = entity->getComponents();
        for (auto& it1 : components ) {
//            if (dynamic_cast<Transform*>(component)) {
//                Transform *t = dynamic_cast<Transform *>(component);
//            } else if (dynamic_cast<Renderer *>(component)) {
//                Renderer *r = dynamic_cast<Renderer *>(component);
//            }
        }
    }
};
