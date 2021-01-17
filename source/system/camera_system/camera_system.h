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
public:
    CameraSystem() = default;
    static void initialize(EntityManager *entityManager,xGame::Application *app);
    static void update(EntityManager *entityManager, float deltaTime);
    static void destroy(EntityManager *entityManager);
};


#endif //GRAPHICS_CAMERA_SYSTEM_H
