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
public:
    Entity* createEntity();
    std::vector<Entity*> getEntities();
};


#endif //GRAPHICS_ENTITY_MANAGER_HPP
