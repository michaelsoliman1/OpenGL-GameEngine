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
#include "../components/collider.h"
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

        auto *wallAlbedo = new xGame::Texture("assets/images/materials/wall/albedo.png");
        auto *wallSpecular = new xGame::Texture("assets/images/materials/wall/specular.png");
        auto *wallRoughness = new xGame::Texture("assets/images/materials/wood/roughness.jpg");

        std::unordered_map<xGame::TextureType, xGame::Texture *> wallTexture;
        wallTexture[xGame::TextureType::ALBEDO] = wallAlbedo;
        wallTexture[xGame::TextureType::SPECULAR] = wallSpecular;
        wallTexture[xGame::TextureType::ROUGHNESS] = wallRoughness;

        // Samplers
        auto* sampler = new xGame::Sampler(GL_LINEAR,GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT,GL_REPEAT);
        auto* wallSampler = new xGame::Sampler();

         // RenderStates
        auto* renderState = new xGame::RenderState(false);
        auto* transparentState = new xGame::RenderState(true);

        // Tints
        glm::vec3 albedoTint = {0,0,0};
        glm::vec3 specularTint = {0,0,0};
        glm::vec3 emissiveTint = {1,1,1};
        glm::vec2 roughnessRange = {0.5,0.5};

        std::unordered_map<std::string , std::any> emissiveProperties;
        emissiveProperties["albedo_tint"] = albedoTint;
        emissiveProperties["specular_tint"] = specularTint;
        emissiveProperties["emissive_tint"] = emissiveTint;
        emissiveProperties["roughness_range"] = roughnessRange;

        // Tints
        glm::vec3 albedoTint2 = {1,1,1};
        glm::vec3 specularTint2 = {1,1,1};
        glm::vec3 emissiveTint2 = {0,0,0};
        glm::vec2 roughnessRange2 = {0.5,0.5};

        std::unordered_map<std::string , std::any> normalProperties;
        normalProperties["albedo_tint"] = albedoTint2;
        normalProperties["specular_tint"] = specularTint2;
        normalProperties["emissive_tint"] = emissiveTint2;
        normalProperties["roughness_range"] = roughnessRange2;

        //materials
        auto *asphaltMaterial = new xGame::Material(defaultShader, asphaltTexture, emissiveProperties, sampler, renderState);
        auto *wallMaterial = new xGame::Material(defaultShader, wallTexture, normalProperties, sampler, renderState);
        auto *rockMaterial = new xGame::Material(defaultShader, wallTexture, normalProperties, sampler, renderState);
        auto *metalMaterial = new xGame::Material(defaultShader, metalTexture, normalProperties, sampler, transparentState);
        auto* woodMaterial = new xGame::Material(defaultShader, woodTexture, normalProperties, sampler, renderState);


        //Camera Entity
        Entity *camera = entityManager->createEntity();
        auto *cameraComponent = new Camera();
        auto* cameraVelocity = new Velocity(0.7);
        auto* cameraController = new CameraController();
        auto* cameraFreeLookController = new CameraFreeLookController();
        auto *cameraTransform = new Transform({10, 3, 0}, {1, 0, 0}, {0, 1, 0});
        auto* cameraCollider = new Collider();
        camera->addComponent(cameraComponent);
        camera->addComponent(cameraTransform);
        camera->addComponent(cameraController);
//        camera->addComponent(cameraFreeLookController);
        camera->addComponent(cameraCollider);
        camera->addComponent(cameraVelocity);
        camera->tag = "Player";


        //Ground
        Entity *ground = entityManager->createEntity();
        auto *groundTransform = new Transform({{0,   0, 0},
                                           {0,   0, 0},
                                          {500, 1, 500}});
        auto *groundRenderer = new MeshRenderer(plane, wallMaterial);
        ground->addComponent(groundTransform);
        ground->addComponent(groundRenderer);

        //Suzanne
        Entity *suzanne = entityManager->createEntity();
        auto *suzanneTransform = new Transform({{0, 4, 0},
                                          {0, 0, 0},
                                          {2, 2, 2}});
        auto *suzanneRenderer= new MeshRenderer(monkey, metalMaterial);
        suzanne->addComponent(suzanneRenderer);
        suzanne->addComponent(suzanneTransform);

//        Entity *reich = entityManager->createEntity();
//        auto *reichTransform = new Transform({{35, 5, 0},
//                                            {0,  0, 0},
//                                            {80,20,80}});
//        auto *reichRenderer = new MeshRenderer(cube, wallMaterial);
//        auto *reichCollider = new Collider();
//        reich->addComponent(reichTransform);
//        reich->addComponent(reichRenderer);
//        reich->addComponent(reichCollider);
//        reich->tag = "wall";

        Entity* skyLightEntity = entityManager->createEntity();
        auto *skyLightComponent = new Light();
        auto *skyLightTransform = new Transform({1, 1, 1}, {0, 0, 0}, {0, -1, 0});
        // SkyLight is a Directional Light but have 3 extra colors to emulate a sky light
        skyLightComponent->enabled = true;
        skyLightComponent->isSkyLight = true;
        skyLightComponent->skyLight.top_color = {1, 1, 1};
        skyLightComponent->skyLight.middle_color= {0.35, 0.35, 0.4};
        skyLightComponent->skyLight.bottom_color = {1, 0, 0};
        skyLightEntity->addComponent(skyLightComponent);
        skyLightEntity->addComponent(skyLightTransform);


        Entity* spotLightEntity = entityManager->createEntity();
        auto *spotLightComponent = new Light();
        auto *spotLightTransform = new Transform({0, 4, 0}, {0,-1,0}, {1,1,1});
        spotLightComponent->enabled = true;
        spotLightComponent->type = xGame::LightType::POINT;
        spotLightEntity->addComponent(spotLightComponent);
        spotLightEntity->addComponent(spotLightTransform);
    };
}