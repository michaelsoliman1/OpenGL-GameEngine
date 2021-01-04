#include "test_state.hpp"
#include "../../components/transform.hpp"
#include "../../components/meshRenderer.hpp"
#include "../../components/camera.h"
#include "../../components/camera_controller.h"

void TestState::onEnter() {
//    renderSystem = new RenderSystem();
//    entityManager = new EntityManager();

    //predefined materials, can be put into a separate file or json! and imported.
    auto* material = new xGame::Material(true, true);
    auto* checkers = new xGame::Material(true, false, true, true);


    Entity* box = entityManager->createEntity();
    Entity* box3 = entityManager->createEntity();
    Entity* box4 = entityManager->createEntity();
    Entity* camera = entityManager->createEntity();

    Entity* plane = entityManager->createEntity();


    auto* cameraComponent = new Camera();
    auto* cameraTransform = new Transform({10, 10, 10},{0, 0, 0}, {0, 1, 0});
    auto* cameraController = new CameraController();
    camera->addComponent(cameraComponent);
    camera->addComponent(cameraTransform);
    camera->addComponent(cameraController);


    auto* transform = new Transform({ {0,0,0}, {0,0,0}, {7,2,7} });
    auto* mesh = new MeshRenderer(material);
    box->addComponent(transform);
    box->addComponent(mesh);

    auto* transform2 = new Transform({ {0,0,0}, {0,0,0}, {500, 1, 500} });
    auto* mesh2 = new MeshRenderer(checkers);
    plane->addComponent(transform2);
    plane->addComponent(mesh2);

    auto* transform4 = new Transform({ {0,2,0}, {0,0,0}, {2,2,2} });
    box4->addComponent(transform4);
    box4->addComponent(mesh);

    //should systems store data ? or there just functions that manipulates comp. data ?
    RenderSystem::initialize(entityManager);
    cameraSystem->initialize(entityManager,app);
}

void TestState::onDraw(float deltaTime) {
    //CameraSystem::update(deltaTime);
    RenderSystem::draw(entityManager);
    cameraSystem->update(entityManager, deltaTime);
}

void TestState::onExit() {
    RenderSystem::destroy(entityManager);
}