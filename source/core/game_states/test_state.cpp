#include "test_state.hpp"
#include "../../components/transform.hpp"
#include "../../components/meshRenderer.hpp"
#include "../../components/camera.h"

void TestState::onEnter() {
//    renderSystem = new RenderSystem();
//    entityManager = new EntityManager();

    //predefined materials, can be put into a separate file or json! and imported.
    auto* material = new xGame::Material(true, true);
    auto* material2 = new xGame::Material(false, false, true);


    Entity* box = entityManager->createEntity();
    Entity* box2 = entityManager->createEntity();
    Entity* box3 = entityManager->createEntity();
    Entity* box4 = entityManager->createEntity();
    Entity* camera = entityManager->createEntity();     

    auto* cameraComponent = new Camera();
    auto* cameraTransform = new Transform({10, 10, 10},{0, 0, 0}, {0, 1, 0});
    camera->addComponent(cameraComponent);
    camera->addComponent(cameraTransform);


    auto* transform = new Transform({ {0,-1,0}, {0,0,0}, {7,2,7} });
    auto* mesh = new MeshRenderer(material);
    box->addComponent(transform);
    box->addComponent(mesh);

    auto* transform2 = new Transform({ {-2,1,-2}, {0,0,0}, {2,2,2} });
    auto* mesh2 = new MeshRenderer(material2);
    box2->addComponent(transform2);
    box2->addComponent(mesh2);

    auto* transform3 = new Transform({ {2,1,-2}, {0,0,0}, {2,2,2} });
    box3->addComponent(transform3);
    box3->addComponent(mesh2);

    auto* transform4 = new Transform({ {-2,1,2}, {0,0,0}, {2,2,2} });
    box4->addComponent(transform4);
    box4->addComponent(mesh);


    RenderSystem::initialize(entityManager);
}

void TestState::onDraw(float deltaTime) {
    //CameraSystem::update(deltaTime);
    RenderSystem::draw(entityManager);
}

void TestState::onExit() {
    RenderSystem::destroy(entityManager);
}