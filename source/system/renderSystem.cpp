//
// Created by ecs on 12/6/2020.
//
#include <vector>


#include "renderSystem.h"
#include "../components/transform.hpp"
#include "../components/meshRenderer.hpp"
#include <../graphics/mesh/common-vertex-types.hpp>
#include <../graphics/mesh/common-vertex-attributes.hpp>


RenderSystem::RenderSystem() {};

void RenderSystem::initialize(EntityManager *entityManager) {
    std::vector<Entity*> entitiesToRender = entityManager->getEntitiesToRender();
    MeshRenderer* meshRenderer;

    for(auto& entity : entitiesToRender) {
        std::vector<IComponent*> components = entity->getComponents();
        for (auto &component: components) {
            if (dynamic_cast<MeshRenderer *>(component)) {
                meshRenderer = dynamic_cast<MeshRenderer *>(component);
            }
        }
        if(meshRenderer!=nullptr){
            meshRenderer->program->create();
            meshRenderer->program->attach("assets/shaders/transform/transform.vert", GL_VERTEX_SHADER);
            meshRenderer->program->attach("assets/shaders/transform/tint.frag", GL_FRAGMENT_SHADER);
            meshRenderer->program->link();

            meshRenderer->quad->create({xGame::setup_buffer_accessors<xGame::ColoredVertex>});
            meshRenderer->quad->setVertexData<xGame::ColoredVertex>(0, {
                    {{-0.5, -0.5, 0},{255,   0,   0, 255}},
                    {{ 0.5, -0.5, 0},{  0, 255,   0, 255}},
                    {{ 0.5,  0.5, 0},{  0,   0, 255, 255}},
                    {{-0.5,  0.5, 0},{255, 255,   0, 255}}
            },GL_STATIC_DRAW);
            meshRenderer->quad->setElementData<GLuint>({
                                                               0, 1, 2,
                                                               2, 3, 0
                                                       },GL_STATIC_DRAW);
            glClearColor(0, 0, 0, 0);
        }
    }
}

void RenderSystem::draw(EntityManager* entityManager) {
    glClear(GL_COLOR_BUFFER_BIT);

    std::vector<Entity*> entitiesToRender = entityManager->getEntitiesToRender();
    MeshRenderer* meshRenderer;
    Transform* transform;
    for(auto& entity : entitiesToRender) {
        std::vector<IComponent*> components = entity->getComponents();
        for (auto& component: components ) {
            if (dynamic_cast<Transform*>(component)) {
                transform = dynamic_cast<Transform *>(component);
            }
            if (dynamic_cast<MeshRenderer *>(component)) {
                meshRenderer = dynamic_cast<MeshRenderer *>(component);
            }
        }
        if(transform!= nullptr && meshRenderer!= nullptr){
            glUseProgram(*meshRenderer->program);

            meshRenderer->program->set("transform", transform->to_mat4());
            meshRenderer->program->set("tint", meshRenderer->tint);

            meshRenderer->quad->draw();
        }
    }
};

void RenderSystem::destroy(EntityManager* entityManager) {
    std::vector<Entity*> entitiesToRender = entityManager->getEntitiesToRender();
    MeshRenderer* meshRenderer;

    for(auto& entity : entitiesToRender) {
        std::vector<IComponent*> components = entity->getComponents();
        for (auto &component: components) {
            if (dynamic_cast<MeshRenderer *>(component)) {
                meshRenderer = dynamic_cast<MeshRenderer *>(component);
            }
        }
        if(meshRenderer!= nullptr){
            meshRenderer->program->destroy();
            meshRenderer->quad->destroy();
        }
    }


}
