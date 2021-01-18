//
// Created by michael on ١٢‏/١‏/٢٠٢١.
//
#include "../entity/entity_manager.hpp"
#include "../graphics/texture/texture.h"
#include "../components/transform.hpp"
#include "../components/meshRenderer.hpp"
#include "../components/camera.h"
#include "../components/camera_controller.h"
#include <../graphics/mesh/common-vertex-attributes.hpp>
#include <memory>

/**
 * Texture -> nameTexture
 * Material -> nameMaterial
 * Mesh -> nameMesh
 * Transform -> nameTransform
 * MeshRenderer -> nameRenderer
 * Light -> lightComponent
 * Camera -> cameraCompenent
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
        xGame::Mesh *monster = xGame::Mesh::loadOBJ("assets/models/Monster/monster.obj");
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
        auto *cameraTransform = new Transform({10, 10, 10}, {0, 0, 0}, {0, 1, 0});
        auto *cameraController = new CameraController();
        camera->addComponent(cameraComponent);
        camera->addComponent(cameraTransform);
        camera->addComponent(cameraController);

        //lights
        Entity* lightEntity = entityManager->createEntity();
        auto *lightComponent = new Light();
        // for light transform {Color, Position, Direction}
        auto *lightTransform = new Transform({1, 0.8, 0.2}, {0, 0, 0}, {-1, -1, -1});
        lightComponent->type = xGame::LightType::DIRECTIONAL;
        lightComponent->enabled = true;///////////////////////////////////////
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
//        Entity *box = entityManager->createEntity();
//        auto *boxTransform = new Transform({{0,  0, 0},
//                                         {0,  0, 0},
//                                         {20, 10, 20}});
//        auto *cubeRenderer = new MeshRenderer(cube, woodMaterial);
//        box->addComponent(boxTransform);
//        box->addComponent(cubeRenderer);


        //Suzanne
        Entity *suzanne = entityManager->createEntity();
        auto *suzanneTransform = new Transform({{0, 4, 0},
                                          {0, 0, 0},
                                          {2, 2, 2}});
        auto *suzanneRenderer= new MeshRenderer(monkey, metalMaterial);
        suzanne->addComponent(suzanneRenderer);
        suzanne->addComponent(suzanneTransform);

        //Monster
        Entity *T_Rex = entityManager->createEntity();
        auto *T_RexTransform = new Transform({{17, 4, 0},
                                                {0, 0, 0},
                                                {5, 0, 5}});
        auto *T_RexRenderer= new MeshRenderer(sphere, metalMaterial);
        T_Rex->addComponent(T_RexRenderer);
        T_Rex->addComponent(T_RexTransform);

        //Room Box
        /*Entity *room = entityManager->createEntity();
        auto *roomTransform = new Transform({{0,  0, 0},
                                            {0,  0, 0},
                                            {500, 500, 500}});
        auto *roomRenderer = new MeshRenderer(cube, woodMaterial);
        room->addComponent(roomTransform);
        room->addComponent(roomRenderer);*/

        //Back Wall
//        Entity *bwall = entityManager->createEntity();
//        auto *bwallTransform = new Transform({{0, 0, 0},
//                                             {90, 90, 90},
//                                             {500, 500, 500}});
//        auto *bwallRenderer = new MeshRenderer(cube, woodMaterial);
//        bwall->addComponent(bwallRenderer);
//        bwall->addComponent(bwallTransform);

        //Left Wall
        /*Entity *lwall = entityManager->createEntity();
        auto *lwallTransform = new Transform({{-100, 0, 0},
                                              {90, 90, 90},
                                              {500, 1, 500}});
        auto *lwallRenderer = new MeshRenderer(plane, metalMaterial);
        lwall->addComponent(lwallRenderer);
        lwall->addComponent(lwallTransform);

        //Front Wall
        Entity *fwall = entityManager->createEntity();
        auto *fwallTransform = new Transform({{0, 0, 0},
                                              {90, 90, 90},
                                              {1, 500, 500}});
        auto *fwallRenderer = new MeshRenderer(cube, woodMaterial);
        fwall->addComponent(fwallRenderer);
        fwall->addComponent(fwallTransform);*/

        //pillar
        Entity *pillar = entityManager->createEntity();
        auto *pillarTransform = new Transform({{0,  0, 0},
                                            {0,  0, 0},
                                            {10, 150, 10}});
        auto *pillarRenderer = new MeshRenderer(sphere, metalMaterial);
        pillar->addComponent(pillarTransform);
        pillar->addComponent(pillarRenderer);

        //pillar 2
        Entity *pillar2 = entityManager->createEntity();
        auto *pillar2Transform = new Transform({{70,  0, 0},
                                               {0,  0, 0},
                                               {10, 150, 10}});
        auto *pillar2Renderer = new MeshRenderer(sphere, metalMaterial);
        pillar2->addComponent(pillar2Transform);
        pillar2->addComponent(pillar2Renderer);

        //pillar 3
        Entity *pillar3 = entityManager->createEntity();
        auto *pillar3Transform = new Transform({{-70,  0, 0},
                                                {0,  0, 0},
                                                {10, 150, 10}});
        auto *pillar3Renderer = new MeshRenderer(sphere, metalMaterial);
        pillar3->addComponent(pillar3Transform);
        pillar3->addComponent(pillar3Renderer);

        //pillar 4
        Entity *pillar4 = entityManager->createEntity();
        auto *pillar4Transform = new Transform({{0,  0, 70},
                                                {0,  0, 0},
                                                {10, 150, 10}});
        auto *pillar4Renderer = new MeshRenderer(sphere, metalMaterial);
        pillar4->addComponent(pillar4Transform);
        pillar4->addComponent(pillar4Renderer);

        //pillar 5
        Entity *pillar5 = entityManager->createEntity();
        auto *pillar5Transform = new Transform({{0,  0, -70},
                                                {0,  0, 0},
                                                {10, 150, 10}});
        auto *pillar5Renderer = new MeshRenderer(sphere, metalMaterial);
        pillar5->addComponent(pillar5Transform);
        pillar5->addComponent(pillar5Renderer);

        //ammo 2
        Entity *ammo2 = entityManager->createEntity();
        auto *ammo2Transform = new Transform({{35,  0, 0},
                                             {0,  0, 0},
                                             {10, 15, 10}});
        auto *ammo2Renderer = new MeshRenderer(cube, woodMaterial);
        ammo2->addComponent(ammo2Transform);
        ammo2->addComponent(ammo2Renderer);

        //ammo 3
        Entity *ammo3 = entityManager->createEntity();
        auto *ammo3Transform = new Transform({{-35,  0, 0},
                                              {0,  0, 0},
                                              {10, 15, 10}});
        auto *ammo3Renderer = new MeshRenderer(cube, woodMaterial);
        ammo3->addComponent(ammo3Transform);
        ammo3->addComponent(ammo3Renderer);

        //ammo 4
        Entity *ammo4 = entityManager->createEntity();
        auto *ammo4Transform = new Transform({{0,  0, 35},
                                              {0,  0, 0},
                                              {10, 15, 10}});
        auto *ammo4Renderer = new MeshRenderer(cube, woodMaterial);
        ammo4->addComponent(ammo4Transform);
        ammo4->addComponent(ammo4Renderer);

        //ammo 5
        Entity *ammo5 = entityManager->createEntity();
        auto *ammo5Transform = new Transform({{0,  0, -35},
                                              {0,  0, 0},
                                              {10, 15, 10}});
        auto *ammo5Renderer = new MeshRenderer(cube, woodMaterial);
        ammo5->addComponent(ammo5Transform);
        ammo5->addComponent(ammo5Renderer);

        //ammo 7
        Entity *ammo7 = entityManager->createEntity();
        auto *ammo7Transform = new Transform({{105,  0, 0},
                                              {0,  0, 0},
                                              {10, 15, 10}});
        auto *ammo7Renderer = new MeshRenderer(cube, woodMaterial);
        ammo7->addComponent(ammo7Transform);
        ammo7->addComponent(ammo7Renderer);

        //ammo 8
        Entity *ammo8 = entityManager->createEntity();
        auto *ammo8Transform = new Transform({{-105,  0, 0},
                                              {0,  0, 0},
                                              {10, 15, 10}});
        auto *ammo8Renderer = new MeshRenderer(cube, woodMaterial);
        ammo8->addComponent(ammo3Transform);
        ammo8->addComponent(ammo3Renderer);

        //ammo 9
        Entity *ammo9 = entityManager->createEntity();
        auto *ammo9Transform = new Transform({{0,  0, 105},
                                              {0,  0, 0},
                                              {10, 15, 10}});
        auto *ammo9Renderer = new MeshRenderer(cube, woodMaterial);
        ammo9->addComponent(ammo9Transform);
        ammo9->addComponent(ammo9Renderer);

        //ammo 10
        Entity *ammo10 = entityManager->createEntity();
        auto *ammo10Transform = new Transform({{0,  0, -105},
                                              {0,  0, 0},
                                              {10, 15, 10}});
        auto *ammo10Renderer = new MeshRenderer(cube, woodMaterial);
        ammo10->addComponent(ammo10Transform);
        ammo10->addComponent(ammo10Renderer);
    };
}

