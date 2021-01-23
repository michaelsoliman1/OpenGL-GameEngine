#include "test_state.hpp"
#include "../scene.hpp"
#include "../system/collision_system/collision_system.h"

void TestState::onEnter() {
    entityManager = new EntityManager();
    movementSystem = new MovementSystem();

    xGame::Scene::loadScene(entityManager);

    RenderSystem::initialize(entityManager);
    CameraSystem::initialize(entityManager, app);
    GUISystem::initialize(app);
}

void TestState::onImmediateGui() {
    GUISystem::onUpdateEnter();
    GUISystem::update(entityManager,app);
    GUISystem::onUpdateExit(app);
}

void TestState::onDraw(float deltaTime) {
    CameraSystem::update(entityManager, deltaTime);
    CollisionSystem::update(entityManager,app,deltaTime);
    movementSystem->update(entityManager, app, deltaTime);
    RenderSystem::draw(entityManager);
    GUISystem::draw();
}

void TestState::onExit() {
    RenderSystem::destroy(entityManager);
    CameraSystem::destroy(entityManager);
    GUISystem::destroy();
}

