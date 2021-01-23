//
// Created by michael on ١٨‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_VELOCITY_H
#define GRAPHICS_VELOCITY_H

class Velocity : public IComponent{
public:
    // we can make it vec3 if we want different velocities in different directions
    float velocity = 1.0f;
    bool canMove = true;

    Velocity(float velocity = 0.005, bool canMove = true) : velocity(velocity), canMove(canMove){};

    void setVelocity(float v){
        velocity = v;
    }
    float getVelocity(){
        return velocity;
    }
};

#endif //GRAPHICS_VELOCITY_H
