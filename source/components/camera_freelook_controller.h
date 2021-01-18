//
// Created by michael on ١٨‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_CAMERA_FREELOOK_CONTROLLER_H
#define GRAPHICS_CAMERA_FREELOOK_CONTROLLER_H

class CameraFreeLookController : public IComponent {
private:
    xGame::Application* app;
    Camera* camera;

    float yaw, pitch;

    float yaw_sensitivity, pitch_sensitivity, fov_sensitivity;

    bool mouse_locked = false;

public:
    void initialize(xGame::Application* application, Camera* camera){
        this->app = application;
        this->camera = camera;
        yaw_sensitivity = pitch_sensitivity = 0.005f;
        fov_sensitivity = glm::pi<float>()/10;

        auto direction = camera->getDirection();
        yaw = glm::atan(-direction.z, direction.x);
        float base_length = glm::sqrt(direction.x * direction.x + direction.z * direction.z);
        pitch = glm::atan(direction.y, base_length);
    }

    void release(){
        if(mouse_locked) {
            mouse_locked = false;
            app->getMouse().unlockMouse(app->getWindow());
        }
    }

    void update(double){
        // if we want to add a power for enemies to paralyze the player maybe
        if(!mouse_locked){
            // TODO all this logic and event handling should be done in cameraSystem | implement later
            glm::vec2 delta = app->getMouse().getMouseDelta();
            pitch -= delta.y * pitch_sensitivity;
            yaw -= delta.x * yaw_sensitivity;
        }
        if(pitch < -glm::half_pi<float>() * 0.99f) pitch = -glm::half_pi<float>() * 0.99f;
        if(pitch >  glm::half_pi<float>() * 0.99f) pitch  = glm::half_pi<float>() * 0.99f;
        yaw = glm::wrapAngle(yaw);

        float fov = camera->getVerticalFieldOfView() + app->getMouse().getScrollOffset().y * fov_sensitivity;
        fov = glm::clamp(fov, glm::pi<float>() * 0.01f, glm::pi<float>() * 0.99f);
        camera->setVerticalFieldOfView(fov);
        camera->setDirection(glm::vec3(glm::cos(yaw), 0, -glm::sin(yaw)) * glm::cos(pitch) + glm::vec3(0, glm::sin(pitch), 0));
    }

    void lockMouse(){
        app->getMouse().lockMouse(app->getWindow());
        mouse_locked = true;
    }
    void unlockMouse(){
        app->getMouse().unlockMouse(app->getWindow());
        mouse_locked = false;
    }

    [[nodiscard]] float getYaw() const {return yaw;}
    [[nodiscard]] float getPitch() const {return pitch;}

    [[nodiscard]] float getYawSensitivity() const {return yaw_sensitivity;}
    [[nodiscard]] float getPitchSensitivity() const {return pitch_sensitivity;}
    [[nodiscard]] float getFieldOfViewSensitivity() const {return fov_sensitivity;}

    void setYaw(float _yaw){
        this->yaw = glm::wrapAngle(_yaw);
    }
    void setPitch(float _pitch){
        const float v = 0.99f*glm::pi<float>()/2;
        if(_pitch > v) _pitch = v;
        else if(_pitch < -v) _pitch = -v;
        this->pitch = _pitch;
    }

    void setYawSensitivity(float sensitivity){this->yaw_sensitivity = sensitivity;}
    void setPitchSensitivity(float sensitivity){this->pitch_sensitivity = sensitivity;}
    void setFieldOfViewSensitivity(float sensitivity){this->fov_sensitivity = sensitivity;}

};

#endif //GRAPHICS_CAMERA_FREELOOK_CONTROLLER_H
