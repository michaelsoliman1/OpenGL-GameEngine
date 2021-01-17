//
// Created by michael on ١٢‏/١‏/٢٠٢١.
//
#include "../entity/entity_manager.hpp"
#include "../graphics/texture/texture.h"
#include "../components/transform.hpp"
#include "../components/meshRenderer.hpp"
#include "../components/camera.h"
#include "../components/camera_controller.h"
#include "../components/light.h"
#include <../graphics/mesh/common-vertex-attributes.hpp>
#include <memory>

/**
 * Texture -> nameTexture
 * Material -> nameMaterial
 * Mesh -> nameMesh
 * Transform -> nameTransform
 * MeshRenderer -> nameRenderer
 * Light -> lightComponent
 * Camera -> cameraComponent
 */

namespace xGame::Scene {
    void loadScene(EntityManager *entityManager) {

        // Shaders
        auto* defaultShader = new xGame::ShaderProgram();
        //auto* skyShader = new xGame::ShaderProgram("assets/shaders/light/sky_transform.vert", "assets/shaders/light/sky.frag");

        //TODO?--loadOBJ // blender export problem
        // meshes
        xGame::Mesh *cube = xGame::Mesh::Cuboid(false);
        xGame::Mesh *sphere = xGame::Mesh::Sphere({32, 16}, false);
        xGame::Mesh *monkey = xGame::Mesh::loadOBJ("assets/models/Suzanne/Suzanne.obj");
        xGame::Mesh *plane = xGame::Mesh::Plane({1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});


        //textures
        auto *moonTexture= new xGame::Texture("assets/images/moon.jpg");

        auto *asphaltAlbedo = new xGame::Texture("assets/images/materials/asphalt/albedo.jpg");
        auto *asphaltSpecular = new xGame::Texture("assets/images/materials/asphalt/specular.jpg");
        auto *asphaltRoughness = new xGame::Texture("assets/images/materials/asphalt/roughness.jpg");
        auto *asphaltEmissive = new xGame::Texture("assets/images/materials/asphalt/emissive.jpg");

        std::unordered_map<xGame::TextureType, xGame::Texture *> asphaltTexture;
        asphaltTexture[xGame::TextureType::ALBEDO] = asphaltAlbedo;
        asphaltTexture[xGame::TextureType::SPECULAR] = asphaltSpecular;
        asphaltTexture[xGame::TextureType::ROUGHNESS] = asphaltRoughness;
        asphaltTexture[xGame::TextureType::EMISSIVE] = asphaltEmissive;

        auto *metalAlbedo = new xGame::Texture("assets/images/materials/metal/albedo.jpg");
        auto *metalSpecular = new xGame::Texture("assets/images/materials/metal/specular.jpg");
        auto *metalRoughness = new xGame::Texture("assets/images/materials/metal/roughness.jpg");

        std::unordered_map<xGame::TextureType, xGame::Texture *> metalTexture;
        metalTexture[xGame::TextureType::ALBEDO] = metalAlbedo;
        metalTexture[xGame::TextureType::SPECULAR] = metalSpecular;
        metalTexture[xGame::TextureType::ROUGHNESS] = metalRoughness;


        auto *woodAlbedo = new xGame::Texture("assets/images/materials/wood/albedo.jpg");
        auto *woodSpecular = new xGame::Texture("assets/images/materials/wood/specular.jpg");
        auto *woodRoughness = new xGame::Texture("assets/images/materials/wood/roughness.jpg");

        std::unordered_map<xGame::TextureType, xGame::Texture *> woodTexture;
        woodTexture[xGame::TextureType::ALBEDO] = woodAlbedo;
        woodTexture[xGame::TextureType::SPECULAR] = woodSpecular;
        woodTexture[xGame::TextureType::ROUGHNESS] = woodRoughness;

        // Samplers
        auto* sampler = new xGame::Sampler(GL_LINEAR,GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT,GL_REPEAT);

        auto* renderState = new xGame::RenderState(false);
        auto* transparentState = new xGame::RenderState(true);

        //materials
        auto *asphaltMaterial = new xGame::Material(defaultShader, asphaltTexture, sampler, renderState);
        auto *metalMaterial = new xGame::Material(defaultShader, metalTexture, sampler, transparentState);
        auto* woodMaterial = new xGame::Material(defaultShader, woodTexture, sampler, renderState);

        //Camera Entity
        Entity *camera = entityManager->createEntity();
        auto *cameraComponent = new Camera();
        auto *cameraController = new CameraController();
        auto *cameraTransform = new Transform({0, 5, 0}, {0, 0, 0}, {0, 1, 0});
//        cameraTransform->addChild(suzanneTransform);
        camera->addComponent(cameraComponent);
        camera->addComponent(cameraTransform);
        camera->addComponent(cameraController);
        camera->tag = "Camera";

        //lights
        Entity* lightEntity = entityManager->createEntity();
        auto *lightComponent = new Light();
        // for light transform -> {Color, Position, Direction}
        auto *lightTransform = new Transform({1, 0.8, 0.2}, {0, 0, 0}, {-1, -1, -1});
        lightComponent->type = xGame::LightType::DIRECTIONAL;
        lightComponent->enabled = true;
        lightEntity->addComponent(lightComponent);
        lightEntity->addComponent(lightTransform);

        Entity* spotLightEntity = entityManager->createEntity();
        auto *spotLightComponent = new Light();
        auto *spotLightTransform = new Transform({1, 0.1, 0.2}, {0, 4, 0}, {3,3,3});
        lightComponent->enabled = true;
        spotLightComponent->type = xGame::LightType::SPOT;
        spotLightComponent->spotAngle.inner = 0.78539816339;
        spotLightComponent->spotAngle.outer = 1.57079632679;
        spotLightEntity->addComponent(spotLightComponent);
        spotLightEntity->addComponent(spotLightTransform);

//        Entity* skyLightEntity = entityManager->createEntity();
//        auto *skyLightComponent = new Light();
//        skyLightComponent->enabled = true;
//        skyLightComponent->isSkyLight = true;
//        skyLightComponent->skyLight.top_color = {1, 0, 0};
//        skyLightComponent->skyLight.middle_color= {0.35, 0.35, 0.4};
//        skyLightComponent->skyLight.bottom_color = {0.25, 1, 0.25};
//        skyLightEntity->addComponent(skyLightComponent);
//        skyLightEntity->addComponent(lightTransform);

        //Ground
        Entity *ground = entityManager->createEntity();
        auto *groundTransform = new Transform({{0,   0, 0},
                                          {0,   0, 0},
                                          {500, 1, 500}});
        auto *groundRenderer = new MeshRenderer(plane, asphaltMaterial);
        ground->addComponent(groundTransform);
        ground->addComponent(groundRenderer);


        //Box
        Entity *box = entityManager->createEntity();
        auto *boxTransform = new Transform({{-4, 0, -4},
                                         {0,  0, 0},
                                         {2,2,2}});
        auto *cubeRenderer = new MeshRenderer(cube, woodMaterial);
        box->addComponent(boxTransform);
        box->addComponent(cubeRenderer);


        //Suzanne
        Entity *suzanne = entityManager->createEntity();
        suzanne->tag = "Player";
        auto *suzanneTransform = new Transform({{6, 2, 0.1},
                                          {0, 0, 0},
                                          {2, 2, 2}});
        suzanneTransform->addChild(cameraTransform);
//        suzanneTransform->freeMe();
        auto *suzanneRenderer= new MeshRenderer(monkey, metalMaterial);
        suzanne->addComponent(suzanneRenderer);
        suzanne->addComponent(suzanneTransform);
    };
}

