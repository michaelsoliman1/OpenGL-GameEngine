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
            meshRenderer->material->program->attach("assets/shaders/texture/transform.vert", GL_VERTEX_SHADER);
            meshRenderer->material->program->attach("assets/shaders/texture/texture.frag", GL_FRAGMENT_SHADER);
//          //TODO? how can i use multiple shaders ?
//          meshRenderer->material->program->attach("assets/shaders/transform/transform.vert", GL_VERTEX_SHADER);
//          meshRenderer->material->program->attach("assets/shaders/transform/tint.frag", GL_FRAGMENT_SHADER);
//
            meshRenderer->material->program->link();
            //TODO? how not to use a texture ?
            meshRenderer->material->sampler->generate();
            meshRenderer->material->texture->load();
        }
    }
    glClearColor(0.4,0.8,1,1.0);
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
    //TODO? sort entities based on their depth and transparency
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

            // Since we will always draw one texture per object, we set the active unit to be 0 and kept it active for the rest of the frame
            meshRenderer->material->texture->setActive();

            // To tell OpenGL which sampler object we will use for this unit, we bind the sampler to unit 0 (which is specified by the 1st parameter of the following function).
            meshRenderer->material->sampler->bind();
            meshRenderer->material->program->set("sampler", 0);

            // instead of setting the parameters for each texture, we just set it to the sampler and each unit that uses that sampler will automatically use these parameters.
            meshRenderer->material->sampler->setParameters();

            // bind the texture with mesh before drawing
            meshRenderer->material->texture->bind();
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
            meshRenderer->material->destroy();
            meshRenderer->model->destroy();
        }
    }
}
