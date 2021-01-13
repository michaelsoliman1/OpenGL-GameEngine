//
// Created by ecs on 1/3/2021.
//

#ifndef OPENGL_GAMEENGINE_PHASE3_SAMPLER_H
#define OPENGL_GAMEENGINE_PHASE3_SAMPLER_H

#include <glad/gl.h>

namespace xGame {
    class Sampler{
    private:
        // Samplers are OpenGL objects so we identify them using a GLuint.
        GLuint sampler;

        GLenum magnification_filter = GL_LINEAR, minification_filter = GL_LINEAR_MIPMAP_LINEAR;
        GLenum wrap_s = GL_REPEAT, wrap_t = GL_REPEAT;
        glm::vec4 border_color = {1,1,1,1};
        GLfloat max_anisotropy = 1.0f;
        GLenum polygon_mode = GL_FILL;

    public:
        Sampler(){
            sampler= 0;
        };
        ~Sampler(){destroy();} //

        //Delete copy constructor and assignment operation
        //This is important for Class that follow the RAII pattern since we destroy the underlying OpenGL object in deconstruction
        //So if we copied the object, one of them can destroy the object(s) while the other still thinks they are valid.
        Sampler(Sampler const &) = delete;
        Sampler &operator=(Sampler const &) = delete;

        void generate() {
            glGenSamplers(1, &sampler);
        };
        void bind(int units){
            // We will bind our sampler to all the units we will use.
            // Since we have 5 maps in our material, we will need 5 units.
            for(GLuint unit = 0; unit < units; ++unit) glBindSampler(unit, sampler);
        }

        //TODO - add parameters
        void setParameters() {
            glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, magnification_filter);
            glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, minification_filter);
            glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, wrap_s);
            glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, wrap_t);
            glSamplerParameterfv(sampler, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(border_color));
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
            glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
//            glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);
        };
        void destroy(){
            glDeleteSamplers(1, &sampler);
        };

    };
}

#endif //OPENGL_GAMEENGINE_PHASE3_SAMPLER_H
