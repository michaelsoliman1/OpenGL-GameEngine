//
// Created by michael on ١٧‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_COLLIDER_H
#define GRAPHICS_COLLIDER_H

class Collider : public IComponent{
    bool isCollided = false;
    glm::vec2 size;
};

#endif //GRAPHICS_COLLIDER_H
