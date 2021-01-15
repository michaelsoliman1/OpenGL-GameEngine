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

};

#endif //GRAPHICS_LIGHT_H
