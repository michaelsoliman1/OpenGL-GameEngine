//
// Created by ecs on 12/6/2020.
//

#include "render_system.h"



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
            meshRenderer->material->program->create();
            if(meshRenderer->material->hasTexture) {
                meshRenderer->material->program->attach("assets/shaders/texture/transform.vert", GL_VERTEX_SHADER);
                meshRenderer->material->program->attach("assets/shaders/texture/texture.frag", GL_FRAGMENT_SHADER);
            }else {
                meshRenderer->material->program->attach("assets/shaders/transform/transform.vert", GL_VERTEX_SHADER);
                meshRenderer->material->program->attach("assets/shaders/transform/tint.frag", GL_FRAGMENT_SHADER);
            }
             meshRenderer->material->program->link();
            if(meshRenderer->material->hasTexture) {
                meshRenderer->material->texture->checkerBoard();
                meshRenderer->createPlane();
            }else
                meshRenderer->createCuboid(true);
        }
    }
    glClearColor(0, 0, 0, 0);
}

void RenderSystem::draw(EntityManager* entityManager) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Entity* cameraEntity = entityManager->getCameraEntity();
    std::vector<IComponent*> components = cameraEntity->getComponents();
    Camera* camera;
    for (auto &component: components) {
        if(dynamic_cast<Camera* > (component)) {
            camera = dynamic_cast<Camera*> (component);
        }
    }

    std::vector<Entity*> entitiesToRender = entityManager->getEntitiesToRender();
    MeshRenderer* meshRenderer;
    Transform* transform;
    for(auto& entity : entitiesToRender) {
        components = entity->getComponents();
        for (auto& component: components ) {
            if (dynamic_cast<Transform*>(component)) {
                transform = dynamic_cast<Transform *>(component);
            }
            if (dynamic_cast<MeshRenderer *>(component)) {
                meshRenderer = dynamic_cast<MeshRenderer *>(component);
            }
        }
        if(transform!= nullptr && meshRenderer!= nullptr){
            meshRenderer->material->renderState->setRenderState();

            glUseProgram(*meshRenderer->material->program);
            if(meshRenderer->material->hasTexture){
                meshRenderer->material->texture->draw();
                meshRenderer->material->program->set("sampler", 0);
            }
            meshRenderer->material->program->set("transform",camera->getVPMatrix()* transform->to_mat4());
            meshRenderer->material->program->set("tint", meshRenderer->material->tint);
            meshRenderer->model->draw();
        }
    }
}

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
            meshRenderer->material->program->destroy();
            meshRenderer->model->destroy();
            meshRenderer->material->texture->destroy();
        }
    }
}
