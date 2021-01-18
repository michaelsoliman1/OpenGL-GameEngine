//
// Created by michael on ١٧‏/١‏/٢٠٢١.
//

#include "collision_system.h"
#include "../components/collider.h"
#include "../components/camera.h"

void CollisionSystem::initialize(EntityManager *entityManager) {

}



void CollisionSystem::update(EntityManager *entityManager,xGame::Application *app, float deltaTime) {
    // loop over all the entities having collider and transform
    auto* transform = new Transform();
    auto* collider = new Collider();
    std::vector<IComponent*> reqComps = {transform, collider};
    std::vector<Entity*> entities = entityManager->getEntitiesHaving(reqComps);
    std::vector<Transform*> transforms;
    std::vector<Collider*> colliders;
    for(auto& entity : entities){
        transform = dynamic_cast<Transform*>(entity->getComponentByType(transform));
        collider = dynamic_cast<Collider*>(entity->getComponentByType(collider));
        transforms.push_back(transform);
        colliders.push_back(collider);
    }
    // check if any collides with another
    for(int i=0;i<transforms.size();i++){
        for(int j = i+1;j<transforms.size();j++){
            double dist = distance(transforms[i]->translation, transforms[j]->translation);
            // if yes ? notify the listeners that those two entities collided
            // for simplicity, we'll assume that all entity cubes ( scale x = y = z)
            // 2.5 added for points at corners
            if(dist<(transforms[i]->scale.x/2 + transforms[j]->scale.x/2)+2.5){
                app->getEventManager()->collisionEvents.notifyListeners(entities[i], entities[j]);
            }
        }
    }
}

void CollisionSystem::destroy(EntityManager *entityManager) {

}
