#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>

class Transform : public IComponent {
public:
    glm::vec3 translation,  rotation, scale;
    std::vector<Transform*> children = {};
    glm::mat4 parentMatrix = glm::mat4(1.0f);
    bool _isFree = false;

    Transform(
            const glm::vec3& translation = {0,0,0},
            const glm::vec3& rotation = {0,0,0},
            const glm::vec3& scale = {1,1,1}
    ): translation(translation), rotation(rotation), scale(scale) {}

    glm::mat4 to_mat4() const {
        return parentMatrix * glm::translate(glm::mat4(1.0f), translation) *
               glm::yawPitchRoll(rotation.y, rotation.x, rotation.z) *
               glm::scale(glm::mat4(1.0f), scale);
    }
    void addChild(Transform* child){
        children.push_back(child);
    }
    void setParentTransform(glm::mat4 _parentMatrix){
        parentMatrix = _parentMatrix;
    }

    std::vector<Transform*> getChildren(){
        return children;
    }
    void deleteChildren(){
        children.clear();
    }

    bool isParent(){return !children.empty();}
    bool isFree(){return _isFree;}
    void freeMe(){
        parentMatrix = glm::mat4(1.0f);
        _isFree = true;
    }

};
