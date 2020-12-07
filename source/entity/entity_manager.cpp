//
// Created by michael on ٧‏/١٢‏/٢٠٢٠.
//

#include "entity_manager.hpp"

Entity* EntityManager::createEntity() {
    Entity* entity = new Entity();
    this->entities.push_back(entity);
    size++;
    return entity;
}

std::vector<Entity*> EntityManager::getEntities() {
    return entities;
}

