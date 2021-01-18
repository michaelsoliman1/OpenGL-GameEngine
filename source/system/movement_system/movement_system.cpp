//
// Created by michael on ١٧‏/١‏/٢٠٢١.
//

#include "movement_system.h"


void MovementSystem::initialize(EntityManager *entityManager, xGame::Application *app) {

}

void MovementSystem::update(EntityManager *entityManager,xGame::Application *app, float deltaTime) {
    //add callback here
    Entity* player = entityManager->getEntityByTag("Player");

    if(player == nullptr) return;

    auto* velocity = new Velocity();
    auto* cameraComponent = new Camera();
    cameraComponent = dynamic_cast<Camera*>(player->getComponentByType(cameraComponent));
    velocity = dynamic_cast<Velocity*>(player->getComponentByType(velocity));

    // the logic for our game is that the player is the camera, so we need to check for the camera != null,
    if(cameraComponent != nullptr){
        if(velocity != nullptr && velocity->canMove){
            app->getEventManager()->keyboardEvents.addListener([cameraComponent,velocity, deltaTime](int key, int scancode, int action, int mods) {
                glm::vec3 position = cameraComponent->getEyePosition();
                std::cout<<"x before : " << position.x <<"\n";
                if(key == GLFW_KEY_W) position += cameraComponent->Forward() * (deltaTime * velocity->velocity);
                if(key == GLFW_KEY_S) position -= cameraComponent->Forward() * (deltaTime * velocity->velocity);;
                if(key == GLFW_KEY_D) position += cameraComponent->Right() * (deltaTime * velocity->velocity);;
                if(key == GLFW_KEY_A) position -= cameraComponent->Right() * (deltaTime * velocity->velocity);;
                std::cout<<"x after : " << position.x<<"\n";
                cameraComponent->setEyePosition(position);
            });
        }
    }


    /// check if something collides with me
    /// if yes ? stop moving in that direction, no : keep moving
    app->getEventManager()->collisionEvents.addListener([](Entity* entity1, Entity* entity2) {
        if(entity1->tag == "Player" || entity2->tag =="Player"){
//            std::cout<<"inn"<<"\n";
        }
    });

}

void MovementSystem::destroy(EntityManager *entityManager) {

}
