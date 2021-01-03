//
// Created by michael on ٣١‏/١٢‏/٢٠٢٠.
//

#include "camera_system.h"

void CameraSystem::initialize(EntityManager *entityManager,xGame::Application *app) {
    //this logic won't work in case there are multiple cameras in the scene
    if(cachedCamera== nullptr){
        cachedCamera = entityManager->getCameraEntity();
    }
    std::vector<IComponent*> components = cachedCamera->getComponents();
    Camera* camera;
    Transform* transform;
    CameraController *controller;

    for (auto &component: components) {
        if (dynamic_cast<Camera * > (component)) {
            camera = dynamic_cast<Camera * > (component);
        }
        if (dynamic_cast<Transform *> (component)) {
            transform = dynamic_cast<Transform *> (component);
        }
        if (dynamic_cast<CameraController *> (component)) {
            controller = dynamic_cast<CameraController *> (component);
        }
    }
    camera->setTransform(transform->to_mat4());
    camera->setupPerspective(glm::pi<float>()/2, static_cast<float>(1280)/720, 0.1f, 100.0f);
    controller->initialize(app, camera);
}
//should make eventManager responsible for listening to events idk || implement later
void CameraSystem::update(EntityManager *entityManager, float deltaTime) {
    //this the worst spaghetti code i've ever wrote :)
    if (cachedCamera == nullptr) {
        cachedCamera = entityManager->getCameraEntity();
    }
    std::vector<IComponent *> components = cachedCamera->getComponents();
    Camera *camera;
    Transform *transform;
    CameraController *controller;
    for (auto &component: components) {
        if (dynamic_cast<Camera * > (component)) {
            camera = dynamic_cast<Camera * > (component);
        }
        if (dynamic_cast<Transform *> (component)) {
            transform = dynamic_cast<Transform *> (component);
        }
        if (dynamic_cast<CameraController *> (component)) {
            controller = dynamic_cast<CameraController *> (component);
        }
    }
    if(camera!=nullptr && controller!=nullptr){
        controller->update(deltaTime);
    }
}

void CameraSystem::destroy(EntityManager *entityManager) {
    if (cachedCamera == nullptr) {
        cachedCamera = entityManager->getCameraEntity();
    }
    std::vector<IComponent *> components = cachedCamera->getComponents();
    Camera *camera;
    Transform *transform;
    CameraController *controller;
    for (auto &component: components) {
        if (dynamic_cast<CameraController *> (component)) {
            controller = dynamic_cast<CameraController *> (component);
        }
    }
    if(controller!=nullptr){
        controller->release();
    }
}
