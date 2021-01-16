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

        GLenum magnificationFilter = GL_LINEAR, minificationFilter = GL_LINEAR_MIPMAP_LINEAR;
        GLenum wrapS = GL_REPEAT, wrapT = GL_REPEAT;
        GLfloat maxAnisotropy = 1.0f;
        GLenum polygonMode = GL_FILL;

    public:
        Sampler(){
            sampler= 0;
        }
        Sampler(GLenum _magnificationFilter, GLenum _minificationFilter, GLenum _wrapS, GLenum _wrapT,
                GLfloat _maxAnisotropy = 1.0f, GLenum _polygonMode = GL_FILL){
            magnificationFilter = _magnificationFilter;
            minificationFilter = _minificationFilter;
            wrapS = _wrapS;
            wrapT = _wrapT;
            maxAnisotropy = _maxAnisotropy;
            polygonMode = _polygonMode;
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
            glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, magnificationFilter);
            glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, minificationFilter);
            glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, wrapS);
            glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, wrapT);
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
            glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
            glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
        };
        void destroy(){
            glDeleteSamplers(1, &sampler);
        };

    };
}

#endif //OPENGL_GAMEENGINE_PHASE3_SAMPLER_H
