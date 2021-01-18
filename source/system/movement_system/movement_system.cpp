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

    auto* transform = new Transform();
    auto* cameraController = new CameraController();
    cameraController = dynamic_cast<CameraController*>(player->getComponentByType(cameraController));
    auto* cameraComponent = new Camera();
    cameraComponent = dynamic_cast<Camera*>(player->getComponentByType(cameraComponent));

    glm::vec3 position = transform->translation;

    // check if something collides with me
    // if yes ? stop moving in that direction, no : keep moving
    app->getEventManager()->collisionEvents.addListener([](Entity* entity1, Entity* entity2) {
        if(entity1->tag == "Player" || entity2->tag =="Player"){
            std::cout<<"inn"<<"\n";
        }
    });

    app->getEventManager()->keyboardEvents.addListener([transform, deltaTime](int key, int scancode, int action, int mods) {
//        if(key == GLFW_KEY_W) transform->translation += glm::vec3(0.001,0,0);
//        if(key == GLFW_KEY_S) transform->translation += glm::vec3(-0.001,0,0);
//        if(key == GLFW_KEY_D) transform->translation += glm::vec3(0,0,0.001);
//        if(key == GLFW_KEY_A) transform->translation += glm::vec3(0,0,-0.001);
    });
}

void MovementSystem::destroy(EntityManager *entityManager) {

}
