//
// Created by michael on ١٧‏/١‏/٢٠٢١.
//

#include "collision_system.h"

void CollisionSystem::initialize(EntityManager *entityManager) {

}

void CollisionSystem::update(EntityManager *entityManager,xGame::Application *app, float deltaTime) {
    // loop over all the entities having collider and transform
    // check if any collides with each other
    // if yes ? notify the listeners that those two entities collided
//     app->getEventManager->collisionEvents.notifyListeners(entity1, entity2)
}

void CollisionSystem::destroy(EntityManager *entityManager) {

}
