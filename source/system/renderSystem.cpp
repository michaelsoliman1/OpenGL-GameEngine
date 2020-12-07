//
// Created by ecs on 12/6/2020.
//
#include "renderSystem.h"
#include "../components/renderer.hpp"
#include "../components/transform.hpp"
RenderSystem::RenderSystem() {};
Renderer RenderSystem::render(Entity list, IComponent* component) {
    for (int i =0; i<list.size(); i++) {
        if (dynamic_cast<Transform *>(component)) {
            Transform *t = dynamic_cast<Transform *>(component);
            list.getComponent(t);
        } else if (dynamic_cast<Renderer *>(component)) {
            Renderer *r = dynamic_cast<Renderer *>(component);
            list.getComponent(r);
        }
    }
};
