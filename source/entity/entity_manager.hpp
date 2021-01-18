//
// Created by michael on ٧‏/١٢‏/٢٠٢٠.
//

#ifndef GRAPHICS_ENTITY_MANAGER_HPP
#define GRAPHICS_ENTITY_MANAGER_HPP

#include <vector>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include "entity.hpp"


class EntityManager{
    int size = 0;
    std::vector<Entity*> entities = {};
    std::vector<Entity*> cachedEntities = {};
public:
    Entity* createEntity();
    Entity* getEntityByTag(const std::string& _tag);
    std::vector<Entity*> getAllEntities();
    //TODO? template<typename T>
    std::vector<Entity*> getEntitiesHaving(IComponent* reqComponent);
    std::vector<Entity*> getEntitiesHaving(const std::vector<IComponent*>& reqComponents);
    Entity* getEntityHaving(IComponent* reqComponent);
    Entity* getEntityHaving(const std::vector<IComponent*>& reqComponents);
    void destroyEntity(int id){};
};


#endif //GRAPHICS_ENTITY_MANAGER_HPP
