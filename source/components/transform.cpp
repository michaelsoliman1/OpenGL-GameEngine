//#pragma once
#include "transform.hpp"

Transform::Transform(glm::vec3 position, glm::vec3 scale, float rotation ){
    position = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);
    rotation = 0.0f;
}

void Transform::setPosition(glm::vec3 position) {
    position = Position;
}

void Transform::setScale(glm::vec3 scale) {
    scale = Scale;
}

void Transform::setRotation(float rotation) {
    rotation = Rotation;
}

glm::vec3 Transform::getPosition(){
    return Position;
}

glm::vec3 Transform::getScale(){
    return Scale;
}

float Transform::getRotation(){
    return Rotation;
}



