//
// Created by michael on ٧‏/١٢‏/٢٠٢٠.
//

#ifndef GRAPHICS_ENTITY_MANAGER_HPP
#define GRAPHICS_ENTITY_MANAGER_HPP

#include <vector>
#include "entity.hpp"


class EntityManager{
    int size = 0;
    //TODO--convert to map of typeIndex,Entity
    std::vector<Entity*> entities = {};
    std::vector<Entity*> cachedEntities = {};
public:
    Entity* createEntity();
    std::vector<Entity*> getEntities();
    //TODO--remove and only pass the components type to be returned
    std::vector<Entity*> getEntitiesToRender();
    Entity* getCameraEntity();
};


#endif //GRAPHICS_ENTITY_MANAGER_HPP
