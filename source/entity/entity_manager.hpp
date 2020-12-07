//
// Created by michael on ٧‏/١٢‏/٢٠٢٠.
//

#ifndef GRAPHICS_ENTITY_MANAGER_HPP
#define GRAPHICS_ENTITY_MANAGER_HPP

#include <vector>
#include "entity.hpp"


class EntityManager{
    std::vector<Entity*> entities = {};
public:
    Entity* createEntity();
    int size();
    std::vector<Entity*> renderEntities();

};


#endif //GRAPHICS_ENTITY_MANAGER_HPP
