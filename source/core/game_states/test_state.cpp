#include "test_state.hpp"
#include "../scene.hpp"

void TestState::onEnter() {
    entityManager = new EntityManager();
    xGame::Scene::loadScene(entityManager);

    RenderSystem::initialize(entityManager);
    CameraSystem::initialize(entityManager, app);
}

void TestState::onDraw(float deltaTime) {
    RenderSystem::draw(entityManager);
    CameraSystem::update(entityManager, deltaTime);
    MovementSystem::update(entityManager, app, deltaTime);

}

void TestState::onExit() {
    RenderSystem::destroy(entityManager);
    CameraSystem::destroy(entityManager);
}