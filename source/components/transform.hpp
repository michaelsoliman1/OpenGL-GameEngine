#pragma once

#include <glm/glm.hpp>
#include "i_component.hpp"

class Transform : public IComponent {
private:
    glm::vec3 translation,  rotation, scale;

    IComponent *component;
public:
    Transform(
            const glm::vec3& translation = {0,0,0},
            const glm::vec3& rotation = {0,0,0},
            const glm::vec3& scale = {1,1,1}
    ): translation(translation), rotation(rotation), scale(scale) {}
};
