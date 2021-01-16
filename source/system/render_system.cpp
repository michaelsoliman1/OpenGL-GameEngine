//
// Created by ecs on 12/6/2020.
//

#include "render_system.h"


void RenderSystem::initialize(EntityManager *entityManager) {
    auto* meshRenderer = new MeshRenderer();
    std::vector<Entity*> entitiesToRender = entityManager->getEntitiesHaving(meshRenderer);
    for(auto& entity : entitiesToRender) {
        meshRenderer = dynamic_cast<MeshRenderer*>(entity->getComponentByType(meshRenderer));
        if(meshRenderer!=nullptr){
            meshRenderer->material->program->create();
            meshRenderer->material->program->attach(GL_VERTEX_SHADER);
            meshRenderer->material->program->attach(GL_FRAGMENT_SHADER);
            meshRenderer->material->program->link();

            meshRenderer->material->sampler->generate();
            for(auto & texture : meshRenderer->material->textures){
                texture.second->load();
            }
        }
    }
    glClearColor(0,0,0,0);
}

void RenderSystem::draw(EntityManager* entityManager) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    auto* cameraComponent = new Camera();
    Entity* cameraEntity = entityManager->getEntityHaving(cameraComponent);
    cameraComponent = dynamic_cast<Camera*>(cameraEntity->getComponentByType(cameraComponent));

    auto* light = new Light();
    std::vector<Entity*> lightEntities = entityManager->getEntitiesHaving(light);

    auto * meshRenderer = new MeshRenderer();
    auto* transform = new Transform();
    std::vector<IComponent*> reqComponents;
    reqComponents.push_back(meshRenderer);
    reqComponents.push_back(transform);
    std::vector<Entity*> entitiesToRender = entityManager->getEntitiesHaving(reqComponents);

    //TODO--sort entities based on their depth and transparency here
    for(auto& entity : entitiesToRender) {
        //add a light entity
        //and what about SkyLight ? should i make it a different component (inherit from light) ?

        transform = dynamic_cast<Transform *>(entity->getComponentByType(transform));
        meshRenderer = dynamic_cast<MeshRenderer *>(entity->getComponentByType(meshRenderer));

        if(transform!= nullptr && meshRenderer!= nullptr){
            // set the renderState for every entity, enable depthTesting, faceCulling, etc.
            meshRenderer->material->renderState->setRenderState();
            // use the passed shader program in the material
            meshRenderer->material->program->useProgram();
            // instead of setting the parameters for each texture, we just set it to the sampler and each unit that uses that sampler will automatically use these parameters.
            meshRenderer->material->sampler->setParameters();
            // we bind the sampler for every texture (i.e: number od textures in the material)
            meshRenderer->material->sampler->bind(meshRenderer->material->textures.size());

            //loop over the texture map in material and bind and set texture
            for (auto& [type, texture] : meshRenderer->material->textures)
            {
                if(texture !=nullptr){
                    switch (type) {
                        case xGame::TextureType::ALBEDO:
                            //bind every texture separately
                            meshRenderer->material->textures[xGame::TextureType::ALBEDO]->setActive(GL_TEXTURE0);
                            // bind the texture with mesh before drawing
                            meshRenderer->material->textures[xGame::TextureType::ALBEDO]->bind();
                            meshRenderer->material->program->set("material.albedo_map", 0);
                            break;
                        case xGame::TextureType::SPECULAR:
                            meshRenderer->material->textures[xGame::TextureType::SPECULAR]->setActive(GL_TEXTURE1);
                            meshRenderer->material->textures[xGame::TextureType::SPECULAR]->bind();
                            meshRenderer->material->program->set("material.specular_map", 1);
                            break;
                        case xGame::TextureType::AMBIENT:
                            meshRenderer->material->textures[xGame::TextureType::AMBIENT]->setActive(GL_TEXTURE2);
                            meshRenderer->material->textures[xGame::TextureType::AMBIENT]->bind();
                            meshRenderer->material->program->set("material.ambient_occlusion_map", 2);
                            break;
                        case xGame::TextureType::ROUGHNESS:
                            meshRenderer->material->textures[xGame::TextureType::ROUGHNESS]->setActive(GL_TEXTURE3);
                            meshRenderer->material->textures[xGame::TextureType::ROUGHNESS]->bind();
                            meshRenderer->material->program->set("material.roughness_map", 3);
                            break;
                        case xGame::TextureType::EMISSIVE:
                            meshRenderer->material->textures[xGame::TextureType::EMISSIVE]->setActive(GL_TEXTURE4);
                            meshRenderer->material->textures[xGame::TextureType::EMISSIVE]->bind();
                            meshRenderer->material->program->set("material.emissive_map", 4);
                            break;
                    }
                }
            }
            // We will go through all the lights and send the enabled ones to the shader.
            int light_index = 0;
            const int MAX_LIGHT_COUNT = 16;
            if(!lightEntities.empty()) {
                for (const auto &lightEntity : lightEntities) {
                    light = dynamic_cast<Light*>(lightEntity->getComponentByType(light));
                    auto* lightTransform = dynamic_cast<Transform*>(lightEntity->getComponentByType(transform));
                    light->setTransform(lightTransform->to_mat4());
                    if(light->isSkyLight){
                        meshRenderer->material->program->set("sky_light.top_color", light->enabled ? light->skyLight.top_color : glm::vec3(0.0f));
                        meshRenderer->material->program->set("sky_light.middle_color", light->enabled ? light->skyLight.middle_color : glm::vec3(0.0f));
                        meshRenderer->material->program->set("sky_light.bottom_color", light->enabled ? light->skyLight.bottom_color : glm::vec3(0.0f));
                    }
                    if (!light->enabled) continue;
                    std::string prefix = "lights[" + std::to_string(light_index) + "].";
                    meshRenderer->material->program->set(prefix + "type", static_cast<int>(light->type));
                    meshRenderer->material->program->set(prefix + "color", light->color);
                    switch (light->type) {
                        case xGame::LightType::DIRECTIONAL:
                            meshRenderer->material->program->set(prefix + "direction", glm::normalize(light->direction));
                            break;
                        case xGame::LightType::POINT:
                            meshRenderer->material->program->set(prefix + "position", light->position);
                            meshRenderer->material->program->set(prefix + "attenuation_constant", light->attenuation.constant);
                            meshRenderer->material->program->set(prefix + "attenuation_linear", light->attenuation.linear);
                            meshRenderer->material->program->set(prefix + "attenuation_quadratic", light->attenuation.quadratic);
                            break;
                        case xGame::LightType::SPOT:
                            meshRenderer->material->program->set(prefix + "position", light->position);
                            meshRenderer->material->program->set(prefix + "direction", glm::normalize(light->direction));
                            meshRenderer->material->program->set(prefix + "attenuation_constant", light->attenuation.constant);
                            meshRenderer->material->program->set(prefix + "attenuation_linear", light->attenuation.linear);
                            meshRenderer->material->program->set(prefix + "attenuation_quadratic", light->attenuation.quadratic);
                            meshRenderer->material->program->set(prefix + "inner_angle", light->spotAngle.inner);
                            meshRenderer->material->program->set(prefix + "outer_angle", light->spotAngle.outer);
                            break;
                        default:
                            break;
                    }
                    light_index++;
                    if (light_index >= MAX_LIGHT_COUNT) break;
                }
                // Since the light array in the shader has a constant size, we need to tell the shader how many lights we sent.
                meshRenderer->material->program->set("light_count", light_index);
            }
            // For each model, we will send the model matrix, model inverse transpose and material properties.
            meshRenderer->material->program->set("object_to_world", transform->to_mat4());
            meshRenderer->material->program->set("object_to_world_inv_transpose", glm::inverse(transform->to_mat4()), true);
            meshRenderer->material->program->set("material.albedo_tint",meshRenderer->material->albedoTint);
            meshRenderer->material->program->set("material.specular_tint", meshRenderer->material->specularTint);
            meshRenderer->material->program->set("material.emissive_tint", meshRenderer->material->emissiveTint);
            meshRenderer->material->program->set("material.roughness_range", meshRenderer->material->roughnessRange);

            // From the camera, we will send the camera position and view-projection matrix.
            meshRenderer->material->program->set("camera_position", cameraComponent->getEyePosition());
            meshRenderer->material->program->set("view_projection", cameraComponent->getVPMatrix());
            // Since we already sent the view-projection matrix already, we will only send the model matrices from the drawNode function.
            // That's why we are now sending an identity matrix as the transform matrix.
            meshRenderer->material->program->set("transform", glm::mat4(1.0f));
            meshRenderer->material->program->set("tint",meshRenderer->material->tint);
            // draw the model on the screen
            meshRenderer->model->draw();
        }
    }
}

void RenderSystem::destroy(EntityManager* entityManager) {
    // should not destroy anything here
}
