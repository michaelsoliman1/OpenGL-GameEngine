//
// Created by michael on ٩‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_LIGHT_H
#define GRAPHICS_LIGHT_H

class Light : public IComponent{
public:
    bool enabled;
    bool isSkyLight;
    xGame::LightType type;

    glm::vec3 color;
    glm::vec3 position; // Used for Point and Spot Lights only
    glm::vec3 direction; // Used for Directional and Spot Lights only
    struct {
        float constant, linear, quadratic;
    } attenuation; // Used for Point and Spot Lights only
    struct {
        float inner, outer;
    } spotAngle; // Used for Spot Lights only
    struct {
        glm::vec3 top_color, middle_color, bottom_color;
    } skyLight;
    Light() = default;

    void setColor(glm::vec3 _color){
        this->color = _color;
    }
    void setPosition(glm::vec3 _position){
        this->position = _position;
    }
    void setDirection(glm::vec3 _direction){
        this->direction = _direction;
    }

    void setTransform(glm::mat4 transform){
        setColor(transform* glm::vec4(0,0,0,1));
        setPosition(transform* glm::vec4(0,0,-1,0) );
        setDirection(transform* glm::vec4(0,1,0,0));
    }

    glm::vec3 getColor() const {return this->color;}
    glm::vec3 getPosition() const {return this->position;}
    glm::vec3 getDirection() const {return  this->direction ;}

};

#endif //GRAPHICS_LIGHT_H
