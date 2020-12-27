#include "test_state.hpp"
#include "../../components/transform.hpp"
#include "../../components/meshRenderer.hpp"

void TestState::onEnter() {

    renderSystem = new RenderSystem();
    entityManager = new EntityManager();
    Entity* box = entityManager->createEntity();
    Entity* box2 = entityManager->createEntity();


    auto* transform = new Transform({ {0.5,0.5,0}, {0,0,0}, {500,20,1} });
    auto* mesh = new MeshRenderer();
    box->addComponent(transform);
    box->addComponent(mesh);

    auto* transform2 = new Transform({ {-0.5,-0.5,0}, {0,0,0}, {500,20,1} });
    auto* mesh2 = new MeshRenderer();
    box2->addComponent(transform2);
    box2->addComponent(mesh2);


    renderSystem->initialize(entityManager);
}

void TestState::onDraw(float deltaTime) {

    renderSystem->draw(entityManager);
}

void TestState::onExit() {
    renderSystem->destroy(entityManager);
}