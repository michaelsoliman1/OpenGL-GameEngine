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
    static double distance(glm::vec3 position1, glm::vec3 position2){
        return sqrt(pow(position2.x - position1.x, 2) +
                       pow(position2.z - position1.z, 2) +
                       pow(position2.y - position1.y, 2) * 1.0);
    }
};


#endif //GRAPHICS_COLLISION_SYSTEM_H
