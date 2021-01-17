//
// Created by michael on ١٧‏/١‏/٢٠٢١.
//

#include "movement_system.h"

void MovementSystem::initialize(EntityManager *entityManager, xGame::Application *app) {

}

void MovementSystem::update(EntityManager *entityManager,xGame::Application *app, float deltaTime) {
    //add callback here
    Entity* camera = entityManager->getEntityByTag("Camera");
    Entity* player = entityManager->getEntityByTag("Player");

    auto* transform = new Transform();
    transform = dynamic_cast<Transform*>(player->getComponentByType(transform));
    auto* cameraController = new CameraController();
    cameraController = dynamic_cast<CameraController*>(camera->getComponentByType(cameraController));

    app->getEventManager()->keyboardEvents.addListener([transform, deltaTime](int key, int scancode, int action, int mods) {
        if(key == GLFW_KEY_W) transform->translation += glm::vec3(0.001,0,0);
        if(key == GLFW_KEY_S) transform->translation += glm::vec3(-0.001,0,0);
        if(key == GLFW_KEY_D) transform->translation += glm::vec3(0,0,0.001);
        if(key == GLFW_KEY_A) transform->translation += glm::vec3(0,0,-0.001);
    });
}

void MovementSystem::destroy(EntityManager *entityManager) {

}
