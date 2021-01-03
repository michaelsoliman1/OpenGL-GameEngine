//
// Created by michael on ٧‏/١٢‏/٢٠٢٠.
//

#include "entity_manager.hpp"
#include "../components/transform.hpp"
#include "../components/meshRenderer.hpp"
#include "../components/camera.h"

Entity* EntityManager::createEntity() {
    Entity* entity = new Entity();
    this->entities.push_back(entity);
    size++;
    return entity;
}

std::vector<Entity*> EntityManager::getEntities() {
    return entities;
}

std::vector<Entity*> EntityManager::getEntitiesToRender() {
    // to be implemented :: add cached list
    // question : can we return the entities with just the transform and mesh meshRenderer components ?
    std::vector<Entity*> entitiesToRender;
    for (auto& entity : this->entities){
        std::vector<IComponent*> components = entity->getComponents();
        Transform* transform;
        MeshRenderer* meshRenderer;
        for (auto& component: components ) {
            if (dynamic_cast<Transform*>(component)) {
                transform = dynamic_cast<Transform *>(component);
            }
            if (dynamic_cast<MeshRenderer *>(component)) {
                meshRenderer = dynamic_cast<MeshRenderer *>(component);
            }
        }
        if (transform!= nullptr && meshRenderer != nullptr){
            entitiesToRender.push_back(entity);
        }
    }
    return entitiesToRender;
}

Entity *EntityManager::getCameraEntity() {
    for (auto& entity : this->entities){
        std::vector<IComponent*> components = entity->getComponents();
        for (auto& component: components ) {
            if (dynamic_cast<Camera*>(component)) {
                return entity;
            }
        }
    }
    return nullptr;
}
