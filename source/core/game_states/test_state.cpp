#include "test_state.hpp"
#include "../scene.hpp"

void TestState::onEnter() {
    entityManager = new EntityManager();
    renderSystem = new RenderSystem();
    cameraSystem = new CameraSystem();

    xGame::Scene::loadScene(entityManager);

    RenderSystem::initialize(entityManager);
    cameraSystem->initialize(entityManager,app);
}

void TestState::onDraw(float deltaTime) {
    RenderSystem::draw(entityManager);
    cameraSystem->update(entityManager, deltaTime);
}

void TestState::onExit() {
    RenderSystem::destroy(entityManager);
    cameraSystem->destroy(entityManager);
}