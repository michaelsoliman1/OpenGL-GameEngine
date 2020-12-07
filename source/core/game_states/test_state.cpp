#include "test_state.hpp"
#include "../../components/transform.hpp"
#include "../../components/meshRenderer.hpp"

void TestState::onEnter() {

    Entity* box = entityManager.createEntity();
    Transform* transform = new Transform({ {0,-100,0}, {0,0,0}, {500,20,1} });
//    MeshRenderer* mesh = new MeshRenderer();
    box->addComponent(transform);
//    box->addComponent(mesh);

    program.create();
    program.attach("assets/shaders/base_shader/quad.vert", GL_VERTEX_SHADER);
    program.attach("assets/shaders/base_shader/color.frag", GL_FRAGMENT_SHADER);
    program.link();

    glGenVertexArrays(1, &vertex_array);

    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
}

void TestState::onDraw(float deltaTime) {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);

    glBindVertexArray(vertex_array);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void TestState::onExit() {
    program.destroy();
    glDeleteVertexArrays(1, &vertex_array);
}