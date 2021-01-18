//
// Created by michael on ٣١‏/١٢‏/٢٠٢٠.
//

#include "camera_system.h"

void CameraSystem::initialize(EntityManager *entityManager,xGame::Application *app) {
    //this logic won't work in case there are multiple cameras in the scene
    auto* cameraComponent = new Camera();
    Entity* cameraEntity = entityManager->getEntityHaving(cameraComponent);

    if(cameraEntity == nullptr) return;

    auto* cameraController = new CameraController;
    auto* cameraTransform = new Transform();
    cameraComponent = dynamic_cast<Camera*>(cameraEntity->getComponentByType(cameraComponent));
    cameraTransform = dynamic_cast<Transform*>(cameraEntity->getComponentByType(cameraTransform));
    cameraController = dynamic_cast<CameraController*>(cameraEntity->getComponentByType(cameraController));
    if( cameraComponent!=nullptr && cameraTransform != nullptr ) {
        //TODO-Debug this , A REALLY STRANGE ERROR!!!!
        cameraComponent->setTransform(cameraTransform->to_mat4());
        cameraComponent->setDirection({1, 0, 0});
        cameraComponent->setupPerspective(glm::pi<float>() / 2, static_cast<float>(1280) / 720, 0.1f, 100.0f);
    }
    if(cameraController!= nullptr)
        cameraController->initialize(app, cameraComponent);
}
//TODO? should make eventManager responsible for listening to events idk || implement later
void CameraSystem::update(EntityManager *entityManager, float deltaTime) {
    auto* cameraController = new CameraController();
    auto* cameraComponent = new Camera();
    auto* cameraTransform = new Transform();

    std::vector<IComponent*> reqComps = {cameraComponent, cameraController};
    auto* cameraEntity = entityManager->getEntityHaving(reqComps);

    if(cameraEntity == nullptr) return;

    cameraComponent = dynamic_cast<Camera*>(cameraEntity->getComponentByType(cameraComponent));
    cameraController = dynamic_cast<CameraController*>(cameraEntity->getComponentByType(cameraController));
    cameraTransform = dynamic_cast<Transform*>(cameraEntity->getComponentByType(cameraTransform));

    //TODO definitely need to change that
    cameraTransform->translation = cameraComponent->getEyePosition();
    cameraTransform->rotation = cameraComponent->getDirection();

    if(cameraController!=nullptr){
        cameraController->update(deltaTime);
    }


}

void CameraSystem::destroy(EntityManager *entityManager) {
    auto* cameraController = new CameraController;
    auto* cameraEntity = entityManager->getEntityHaving(cameraController);
    if(cameraEntity == nullptr) return;
    cameraController = dynamic_cast<CameraController*>(cameraEntity->getComponentByType(cameraController));
    if(cameraController!=nullptr){
        cameraController->release();
    }
}
