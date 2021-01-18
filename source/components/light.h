//
// Created by michael on ٩‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_LIGHT_H
#define GRAPHICS_LIGHT_H

class Light : public IComponent{
public:
    bool enabled = true;
    bool isSkyLight = false;
    xGame::LightType type = xGame::LightType::DIRECTIONAL;

    glm::vec3 color = {1, 1, 1};
    glm::vec3 position = {0, 2, 0}; // Used for Point and Spot Lights only
    glm::vec3 direction = {0, -1, 0}; // Used for Directional and Spot Lights only
    struct {
        float constant = 0.0, linear = 0.0, quadratic = 1.0;
    } attenuation; // Used for Point and Spot Lights only
    struct {
        float inner = glm::quarter_pi<float>(), outer = glm::half_pi<float>();
    } spotAngle; // Used for Spot Lights only
    struct {
        glm::vec3 top_color = {1, 1, 1}, middle_color = {0.35, 0.35, 0.4}, bottom_color = {0.25, 0.25, 0.25};
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
