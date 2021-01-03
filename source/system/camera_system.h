//
// Created by michael on ٣١‏/١٢‏/٢٠٢٠.
//

#ifndef GRAPHICS_CAMERA_SYSTEM_H
#define GRAPHICS_CAMERA_SYSTEM_H

#include "../entity/entity_manager.hpp"
#include "../entity/entity_manager.hpp"
#include "../components/transform.hpp"
#include "../components/camera.h"
#include "../components/camera_controller.h"
#include <application.hpp>

class CameraSystem {
    Entity* cachedCamera;
public:
    CameraSystem() = default;
    void initialize(EntityManager *entityManager,xGame::Application *app);
    void update(EntityManager *entityManager, float deltaTime);
    void destroy(EntityManager *entityManager);
};


#endif //GRAPHICS_CAMERA_SYSTEM_H
