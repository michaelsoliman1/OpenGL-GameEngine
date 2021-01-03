//
// Created by michael on ٣١‏/١٢‏/٢٠٢٠.
//

#ifndef GRAPHICS_CAMERA_SYSTEM_H
#define GRAPHICS_CAMERA_SYSTEM_H

#include "../entity/entity_manager.hpp"
#include "../entity/entity_manager.hpp"
#include "../components/transform.hpp"
#include "../components/camera.h"

class camera_system {
public:
    static void initialize(EntityManager *entityManager);
    static void update(EntityManager *entityManager);
    static void destroy(EntityManager *entityManager);
};


#endif //GRAPHICS_CAMERA_SYSTEM_H
