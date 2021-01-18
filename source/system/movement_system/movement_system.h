//
// Created by michael on ١٧‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_MOVEMENT_SYSTEM_H
#define GRAPHICS_MOVEMENT_SYSTEM_H

#include <application.hpp>
#include "../entity/entity_manager.hpp"
#include "../components/transform.hpp"
#include "../components/velocity.h"
#include "../components/camera.h"
#include "../components/camera_controller.h"
#include "../components/camera_freelook_controller.h"


class MovementSystem {
public:
    MovementSystem() = default;
    glm::vec3 playerPosition;
    void initialize(EntityManager *entityManager,xGame::Application *app);
    void update(EntityManager *entityManager,xGame::Application *app, float deltaTime);
    void destroy(EntityManager *entityManager);
};


#endif //GRAPHICS_MOVEMENT_SYSTEM_H
