//
// Created by michael on ١٧‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_COLLIDER_H
#define GRAPHICS_COLLIDER_H

class Collider : public IComponent{
public:
    bool enabled = true;
    glm::vec3 position;
    glm::vec3 scale;
};

#endif //GRAPHICS_COLLIDER_H
