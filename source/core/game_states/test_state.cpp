#include "test_state.hpp"
#include "../scene.hpp"
#include "../system/collision_system/collision_system.h"

void TestState::onEnter() {
    entityManager = new EntityManager();
    movementSystem = new MovementSystem();

    xGame::Scene::loadScene(entityManager);

    RenderSystem::initialize(entityManager);
    CameraSystem::initialize(entityManager, app);
}

void TestState::onDraw(float deltaTime) {
    CameraSystem::update(entityManager, deltaTime);
    CollisionSystem::update(entityManager,app,deltaTime);
    movementSystem->update(entityManager, app, deltaTime);
    RenderSystem::draw(entityManager);
}

void TestState::onExit() {
    RenderSystem::destroy(entityManager);
    CameraSystem::destroy(entityManager);
}