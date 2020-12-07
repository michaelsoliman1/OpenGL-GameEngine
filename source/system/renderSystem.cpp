//
// Created by ecs on 12/6/2020.
//
#include "renderSystem.h"
#include "../components/renderer.hpp"
#include "../components/transform.hpp"
#include <vector>

RenderSystem::RenderSystem() {};
Renderer RenderSystem::render(EntityManager entityList, IComponent* component) {
    std::vector<Entity*> entities = entityList.renderEntities();
    std::vector<IComponent*> components = *entities.renderComponents();
    for (auto&  it : entities) {
        for (auto& it1 : components ) {
            if (dynamic_cast<Transform*>(component)) {
                Transform *t = dynamic_cast<Transform *>(component);
                entities*.getComponent(t);
            } else if (dynamic_cast<Renderer *>(component)) {
                Renderer *r = dynamic_cast<Renderer *>(component);
                entities*.getComponent(r);
            }
        }
    }
};
