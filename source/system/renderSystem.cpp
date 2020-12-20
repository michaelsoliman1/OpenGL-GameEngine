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

void RenderSystem::initialize(Entity *entity) {
    std::vector<IComponent*> components = entity->getComponents();
    MeshRenderer* meshRenderer;

    for (auto& component: components ) {
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

void RenderSystem::draw(Entity* entity) {
    std::vector<IComponent*> components = entity->getComponents();
    Transform* transform;
    MeshRenderer* meshRenderer;
    for (auto& component: components ) {
        if (dynamic_cast<Transform*>(component)) {
            transform = dynamic_cast<Transform *>(component);
        }
        if (dynamic_cast<MeshRenderer *>(component)) {
            meshRenderer = dynamic_cast<MeshRenderer *>(component);
        }
    }
    if(transform!= nullptr && meshRenderer!= nullptr){
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(*meshRenderer->program);

        meshRenderer->program->set("transform", transform->to_mat4());
        meshRenderer->program->set("tint", glm::vec4(1,1,1,1));

        meshRenderer->quad->draw();
    }



//    std::vector<Entity*> entities = entityList.getEntities();
//    for (auto&  entity : entities) {
//        std::vector<IComponent*> components = entity->getComponents();
//        for (auto& component: components ) {
////            if (dynamic_cast<Transform*>(component)) {
////                Transform *t = dynamic_cast<Transform *>(component);
////            } else if (dynamic_cast<Renderer *>(component)) {
////                Renderer *r = dynamic_cast<Renderer *>(component);
////            }
//        }
//    }
};

void RenderSystem::destroy(Entity *entity) {
    std::vector<IComponent*> components = entity->getComponents();
    MeshRenderer* meshRenderer;
    for (auto& component: components ) {
        if (dynamic_cast<MeshRenderer *>(component)) {
            meshRenderer = dynamic_cast<MeshRenderer *>(component);
        }
    }
    if(meshRenderer!= nullptr){
        meshRenderer->program->destroy();
        meshRenderer->quad->destroy();
    }

}
