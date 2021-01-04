#include "test_state.hpp"
#include "../../components/transform.hpp"
#include "../../components/meshRenderer.hpp"
#include "../../components/camera.h"
#include "../../components/camera_controller.h"

void TestState::onEnter() {
    entityManager = new EntityManager();
    renderSystem = new RenderSystem();
    cameraSystem = new CameraSystem();

    //predefined data, can be put into a separate file or json! and imported.

    //can i add mesh_utils functions inside mesh class and return pointer 3latol? what is a good practice!
    //is it right t create meshes here? how can i create different meshes in onInitialize ?
    xGame::Mesh* meshCube = new xGame::Mesh();
    xGame::mesh_utils::Cuboid(*meshCube, true);
    xGame::Mesh* meshPlane = new xGame::Mesh();
    xGame::mesh_utils::Plane(*meshPlane, {1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});;

    //moon texture
    auto* moonTexture = new xGame::Texture("assets/images/moon.jpg");

    //materials
    auto* checkersMaterial = new xGame::Material(nullptr, true, false);
    auto* moonMat = new xGame::Material(moonTexture,true, true, true);

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


    //Box1, Box2
    Entity* box = entityManager->createEntity();
    Entity* box1 = entityManager->createEntity();
    auto* transform = new Transform({ {0,0,0}, {0,0,0}, {7,2,7} });
    auto* mesh = new MeshRenderer(meshCube,moonMat);
    box->addComponent(transform);
    box->addComponent(mesh);

    auto* transform1 = new Transform({ {0,2,0}, {0,0,0}, {2,2,2} });
    box1->addComponent(transform1);
    box1->addComponent(mesh);

    //should systems store data ? or there just functions that manipulates comp. data ?
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