#include "test_state.hpp"
#include "../../components/transform.hpp"
#include "../../components/meshRenderer.hpp"
#include "../../components/camera.h"
#include "../../components/camera_controller.h"
#include "../../components/light.h"

void TestState::onEnter() {
    entityManager = new EntityManager();
    renderSystem = new RenderSystem();
    cameraSystem = new CameraSystem();

    //textures
    auto* moonTexture = new xGame::Texture("assets/images/moon.jpg");

    auto* asphalt_albedo = new xGame::Texture("assets/images/materials/asphalt/albedo.jpg");
    auto* asphalt_specular = new xGame::Texture("assets/images/materials/asphalt/specular.jpg");
    auto* asphalt_roughness = new xGame::Texture("assets/images/materials/asphalt/roughness.jpg");
    auto* asphalt_emissive = new xGame::Texture("assets/images/materials/asphalt/emissive.jpg");

    std::unordered_map<xGame::TextureType, xGame::Texture*> asphalt;
    asphalt[xGame::TextureType::ALBEDO] = asphalt_albedo;
    asphalt[xGame::TextureType::SPECULAR] = asphalt_specular;
    asphalt[xGame::TextureType::ROUGHNESS] = asphalt_roughness;
    asphalt[xGame::TextureType::EMISSIVE] = asphalt_emissive;

    auto* metal_albedo = new xGame::Texture("assets/images/materials/metal/albedo.jpg");
    auto* metal_specular = new xGame::Texture("assets/images/materials/metal/specular.jpg");
    auto* metal_roughness = new xGame::Texture("assets/images/materials/metal/roughness.jpg");

    std::unordered_map<xGame::TextureType, xGame::Texture*> metal;
    metal[xGame::TextureType::ALBEDO] = metal_albedo;
    metal[xGame::TextureType::SPECULAR] = metal_specular;
    metal[xGame::TextureType::ROUGHNESS] = metal_roughness;

    auto* light = new Light();
    light->type = xGame::LightType::DIRECTIONAL;
    light->enabled = true;
    light->color = {1, 0.8, 0.2};
    light->direction = {-1, -1, -1};
    light->position = {0, 1, 5};
    light->attenuation = {0, 0, 1};
    light->spot_angle = {glm::pi<float>()/4, glm::pi<float>()/2};


    //predefined data, can be put into a separate file or json! and imported.

    //TODO--
    //create mesh objects
    // loadOBJ
    xGame::Mesh* cube = xGame::Mesh::Cuboid(false);
    xGame::Mesh* sphere = xGame::Mesh::Sphere({32, 16}, false);
    xGame::Mesh* suzanne = xGame::Mesh::loadOBJ( "assets/models/Suzanne/Suzanne.obj");
    xGame::Mesh* meshPlane = xGame::Mesh::Plane({1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});




    //materials
    auto* checkersMaterial = new xGame::Material(asphalt, false, true, false, true);
    //TODO when Face Culling is true, Depth Testing is enabled even when i pass false !!
    auto* moonMat = new xGame::Material(metal,false, true, true,true);

    //Camera Entity
    Entity* camera = entityManager->createEntity();
    auto* cameraComponent = new Camera();
    auto* cameraTransform = new Transform({10, 10, 10},{0, 0, 0}, {0, 1, 0});
    auto* cameraController = new CameraController();
    camera->addComponent(cameraComponent);
    camera->addComponent(cameraTransform);
    camera->addComponent(cameraController);

    //Ground
    Entity* plane = entityManager->createEntity();
    auto* transform2 = new Transform({ {0,0,0}, {0,0,0}, {500, 1, 500} });
    auto* mesh2 = new MeshRenderer(meshPlane,checkersMaterial);
    plane->addComponent(transform2);
    plane->addComponent(mesh2);
    plane->addComponent(light);


    //Box1, Box2
    Entity* box = entityManager->createEntity();
    Entity* box1 = entityManager->createEntity();
    auto* transform = new Transform({ {0,1,0}, {0,0,0}, {10,2,10} });
    auto* meshCube = new MeshRenderer(cube,moonMat);
    box->addComponent(transform);
    box->addComponent(meshCube);

    auto* transform1 = new Transform({ {0,4 ,0}, {0,0,0}, {2,2,2} });
    auto* meshSuzanne = new MeshRenderer(suzanne,moonMat);
    box1->addComponent(transform1);
    box1->addComponent(meshSuzanne);
    box1->addComponent(light);

    //TODO?
    //should systems store data ? or there just functions that manipulates components data ?
    //da eshta
    RenderSystem::initialize(entityManager);
    cameraSystem->initialize(entityManager,app);
}

void TestState::onDraw(float deltaTime) {
    RenderSystem::draw(entityManager);
    cameraSystem->update(entityManager, deltaTime);
}

void TestState::onExit() {
    RenderSystem::destroy(entityManager);
    cameraSystem->destroy(entityManager);
}