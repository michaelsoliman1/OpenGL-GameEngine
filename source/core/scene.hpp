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
 */

namespace xGame::Scene {
    void loadScene(EntityManager *entityManager) {

        //lights
        auto *light = new Light();
        light->type = xGame::LightType::DIRECTIONAL;
        light->enabled = true;
        light->color = {1, 0.8, 0.2};
        light->direction = {-1, -1, -1};

        auto *skyLight = new Light();
        skyLight->enabled = false;
        skyLight->isSkyLight = true;
        skyLight->skyLight.top_color = {0, 0, 0};
        skyLight->skyLight.middle_color= {0.35, 0.35, 0.4};
        skyLight->skyLight.bottom_color = {0.25, 1, 0.25};

        // Shaders
        auto* defaultShader = new xGame::ShaderProgram();
        //auto* skyShader = new xGame::ShaderProgram("assets/shaders/light/sky_transform.vert", "assets/shaders/light/sky.frag");

        //TODO--loadOBJ
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
        auto *cameraTransform = new Transform({10, 10, 10}, {0, 0, 0}, {0, 1, 0});
        auto *cameraController = new CameraController();
        camera->addComponent(cameraComponent);
        camera->addComponent(cameraTransform);
        camera->addComponent(cameraController);

        //Ground
        Entity *ground = entityManager->createEntity();
        auto *groundTransform = new Transform({{0,   0, 0},
                                          {0,   0, 0},
                                          {500, 1, 500}});
        auto *groundRenderer = new MeshRenderer(plane, asphaltMaterial);
        ground->addComponent(groundTransform);
        ground->addComponent(groundRenderer);
        ground->addComponent(light);
//        ground->addComponent(skyLight);


        //Box
        Entity *box = entityManager->createEntity();
        auto *boxTransform = new Transform({{0,  1, 0},
                                         {0,  0, 0},
                                         {10, 2, 10}});
        auto *cubeRenderer = new MeshRenderer(cube, woodMaterial);
        box->addComponent(boxTransform);
        box->addComponent(cubeRenderer);
        box->addComponent(light);
//        box->addComponent(skyLight);


        //Suzanne
        Entity *suzanne = entityManager->createEntity();
        auto *suzanneTransform = new Transform({{0, 4, 0},
                                          {0, 0, 0},
                                          {2, 2, 2}});
        auto *suzanneRenderer= new MeshRenderer(monkey, metalMaterial);
        suzanne->addComponent(suzanneRenderer);
        suzanne->addComponent(suzanneTransform);
        suzanne->addComponent(light);
//        suzanne->addComponent(skyLight);
    };
}

