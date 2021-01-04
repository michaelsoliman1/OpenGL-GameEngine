//
// Created by ecs on 1/3/2021.
//

#ifndef OPENGL_GAMEENGINE_PHASE3_SAMPLER_H
#define OPENGL_GAMEENGINE_PHASE3_SAMPLER_H

#include <glad/gl.h>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "../mesh/mesh.hpp"
#include "../../core/camera/camera.hpp"
#include "../../core/camera/controllers/fly_camera_controller.hpp"
#include "../texture/texture.h"
#include "../../components/transform.hpp"
#include "../shader/shader.hpp"
#include <fstream>
#include <unordered_map>
using namespace std;
#include "../utils/data-types.h"
#include <memory>

namespace xGame {
    class Sampler{
    private:
        std::unordered_map<std::string, std::unique_ptr<xGame::Mesh>> meshes;
        std::shared_ptr<Transform> root;
        GLuint sampler;
        GLuint texture;
        std::unordered_map<std::string, GLuint> textures;
        GLenum magnification_filter = GL_LINEAR, minification_filter = GL_LINEAR_MIPMAP_LINEAR;
        GLenum wrap_s = GL_REPEAT, wrap_t = GL_REPEAT;
        glm::vec4 border_color = {1,1,1,1};
        GLfloat max_anisotropy = 1.0f;
        GLenum polygon_mode = GL_FILL;
        xGame::Camera camera;
        xGame::FlyCameraController camera_controller;
        struct Transform {
            glm::vec4 tint;
            glm::vec3 translation, rotation, scale;
            std::optional<std::string> mesh;
            std::string texture;
            std::unordered_map<std::string, std::shared_ptr<Transform>> children;

            [[nodiscard]] glm::mat4 to_mat4() const {
                return glm::translate(glm::mat4(1.0f), translation) *
                       glm::yawPitchRoll(rotation.y, rotation.x, rotation.z) *
                       glm::scale(glm::mat4(1.0f), scale);
            }
        };
        xGame::ShaderProgram shader;

    public:
        Sampler(){
            glGenSamplers(1, &sampler);
        };
        ~Sampler(){destroy();} //

        //Delete copy constructor and assignment operation
        //This is important for Class that follow the RAII pattern since we destroy the underlying OpenGL object in deconstruction
        //So if we copied the object, one of them can destroy the object(s) while the other still thinks they are valid.
        Sampler(Sampler const &) = delete;
        Sampler &operator=(Sampler const &) = delete;

        void create(const void *data, glm::ivec2 size,bool generate_mipmap = true);
        void destroy();
        void drawNode(const std::shared_ptr<Transform>& node, const glm::mat4& parent_transform_matrix);
        void onDraw(double deltaTime);

    };
}

#endif //OPENGL_GAMEENGINE_PHASE3_SAMPLER_H
