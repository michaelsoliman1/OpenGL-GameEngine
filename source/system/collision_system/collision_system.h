//
// Created by michael on ١٧‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_COLLISION_SYSTEM_H
#define GRAPHICS_COLLISION_SYSTEM_H

#include <vector>
#include <application.hpp>
#include "../entity/entity_manager.hpp"
#include "../components/transform.hpp"

class CollisionSystem {
public:
    static void initialize(EntityManager *entityManager);
    static void update(EntityManager *entityManager,xGame::Application *app, float deltaTime);
    static void destroy(EntityManager *entityManager);
};


#endif //GRAPHICS_COLLISION_SYSTEM_H
