//
// Created by michael on ٣١‏/١٢‏/٢٠٢٠.
//

#include "camera_system.h"

void CameraSystem::initialize(EntityManager *entityManager,xGame::Application *app) {
    //this logic won't work in case there are multiple cameras in the scene
    auto* cameraComponent = new Camera();
    Entity* cameraEntity = entityManager->getEntityHaving(cameraComponent);

    auto* cameraController = new CameraController;
    auto* cameraTransform = new Transform();
    cameraComponent = dynamic_cast<Camera*>(cameraEntity->getComponentByType(cameraComponent));
    cameraTransform = dynamic_cast<Transform*>(cameraEntity->getComponentByType(cameraTransform));
    cameraController = dynamic_cast<CameraController*>(cameraEntity->getComponentByType(cameraController));
    if( cameraComponent!=nullptr && cameraTransform != nullptr ) {
        cameraComponent->setTransform(cameraTransform->to_mat4());
        cameraComponent->setupPerspective(glm::pi<float>() / 2, static_cast<float>(1280) / 720, 0.1f, 100.0f);
    }
    if(cameraController!= nullptr)
        cameraController->initialize(app, cameraComponent);
}
//TODO? should make eventManager responsible for listening to events idk || implement later
void CameraSystem::update(EntityManager *entityManager, float deltaTime) {
    auto* cameraComponent = new Camera();
    auto* cameraEntity = entityManager->getEntityHaving(cameraComponent);

    auto* cameraController = new CameraController;
    cameraComponent = dynamic_cast<Camera*>(cameraEntity->getComponentByType(cameraComponent));
    cameraController = dynamic_cast<CameraController*>(cameraEntity->getComponentByType(cameraController));
    if(cameraComponent!=nullptr && cameraController!=nullptr){
        cameraController->update(deltaTime);
    }
}

void CameraSystem::destroy(EntityManager *entityManager) {
    auto* cameraController = new CameraController;
    auto* cameraEntity = entityManager->getEntityHaving(cameraController);
    cameraController = dynamic_cast<CameraController*>(cameraEntity->getComponentByType(cameraController));
    if(cameraController!=nullptr){
        cameraController->release();
    }
}
