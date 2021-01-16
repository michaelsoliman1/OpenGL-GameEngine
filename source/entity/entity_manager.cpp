//
// Created by michael on ٧‏/١٢‏/٢٠٢٠.
//

#include "entity_manager.hpp"

Entity* EntityManager::createEntity() {
    auto* entity = new Entity(size);
    this->entities.push_back(entity);
    size++;
    return entity;
}

std::vector<Entity*> EntityManager::getAllEntities() {
    return entities;
}

// search only for on component
std::vector<Entity *> EntityManager::getEntitiesHaving(IComponent *reqComponent) {
    // return a vector of entities satisfying the condition
    std::vector<Entity *> matchedEntities;
    for(auto& entity : entities){
        IComponent* c = entity->getComponentByType(reqComponent);
        if(c != nullptr){
            matchedEntities.push_back(entity);
        }
    }
    return matchedEntities;
}

std::vector<Entity *> EntityManager::getEntitiesHaving(const std::vector<IComponent*>& reqComponents) {
    // return a vector of entities satisfying the condition
    std::vector<Entity *> matchedEntities;
    for(auto& entity : entities){
        bool isMatched = true;
        for(auto& component : reqComponents){
            if(entity->getComponentByType(component)== nullptr){
                isMatched = false;
            }
        }
        if(isMatched){
            matchedEntities.push_back(entity);
        }
    }
    return matchedEntities;
}

Entity* EntityManager::getEntityHaving(const std::vector<IComponent *> &reqComponents) {
    // return just one entity satisfying the condition
    for (auto &entity : entities) {
        for (auto &component : reqComponents) {
            if (entity->getComponentByType(component) != nullptr) {
                // found, return the entity
                return entity;
            }
        }
    }
    return nullptr;
}

// search only for on component
Entity *EntityManager::getEntityHaving(IComponent *reqComponent) {
    // return just one entity satisfying the condition
    for(auto& entity : entities){
        if(entity->getComponentByType(reqComponent)!= nullptr){
            return entity;
        }
    }
    return nullptr;
}





