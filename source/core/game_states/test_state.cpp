#include "test_state.hpp"
#include "../../components/transform.hpp"
#include "../../components/meshRenderer.hpp"

void TestState::onEnter() {

    renderSystem = new RenderSystem();

    auto* transform = new Transform({ {0,-100,0}, {0,0,0}, {500,20,1} });
    auto* mesh = new MeshRenderer();
    box->addComponent(transform);
    box->addComponent(mesh);

    renderSystem->initialize(box);
}

void TestState::onDraw(float deltaTime) {

    renderSystem->draw(box);;
}

void TestState::onExit() {
    renderSystem->destroy(box);
}