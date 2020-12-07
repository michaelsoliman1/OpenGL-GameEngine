#pragma once

#include <glm/glm.hpp>

class Transform : public IComponent {
private:
    glm::vec3 translation,  rotation, scale;

public:
    Transform(
            const glm::vec3& translation = {0,0,0},
            const glm::vec3& rotation = {0,0,0},
            const glm::vec3& scale = {1,1,1}
    ): translation(translation), rotation(rotation), scale(scale) {}
};
