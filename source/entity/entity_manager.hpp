//
// Created by michael on ٧‏/١٢‏/٢٠٢٠.
//

#ifndef GRAPHICS_ENTITY_MANAGER_HPP
#define GRAPHICS_ENTITY_MANAGER_HPP

#include <vector>
#include "entity.hpp"


class EntityManager{
    int size = 0;
    std::vector<Entity*> entities = {};
    std::vector<Entity*> cachedEntities = {};
public:
    Entity* createEntity();
    std::vector<Entity*> getEntities();
    std::vector<Entity*> getEntitiesToRender();
};


#endif //GRAPHICS_ENTITY_MANAGER_HPP
