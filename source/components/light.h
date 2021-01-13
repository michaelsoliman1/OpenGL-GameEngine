//
// Created by michael on ٩‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_LIGHT_H
#define GRAPHICS_LIGHT_H

class Light : public IComponent{
public:
    xGame::LightType type;
    bool enabled;
    glm::vec3 color;
    glm::vec3 position; // Used for Point and Spot Lights only
    glm::vec3 direction; // Used for Directional and Spot Lights only
    struct {
        float constant, linear, quadratic;
    } attenuation; // Used for Point and Spot Lights only
    struct {
        float inner, outer;
    } spot_angle; // Used for Spot Lights only
    Light() = default;

};

#endif //GRAPHICS_LIGHT_H
