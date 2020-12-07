#pragma once

#include <glm/glm.hpp>
#include "i_component.hpp"

    class Transform : public IComponent {
    private:
        glm::vec3 Position;
        glm::vec3 Scale;
        float Rotation;
        IComponent *component;
    public:
        Transform() = default;
        Transform(glm::vec3 position, glm::vec3 scale, float rotation);
        void setPosition(glm::vec3 position);
        void setScale(glm::vec3 scale);
        void setRotation(float Rotation);

        glm::vec3 getPosition();
        glm::vec3 getScale();
        float getRotation();
    };
