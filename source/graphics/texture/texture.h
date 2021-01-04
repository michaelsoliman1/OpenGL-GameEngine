//
// Created by michael on ٢‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H


#include <glad/gl.h>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../utils/data-types.h"

namespace xGame{
    class Texture {
    private:
        GLuint texture;
        GLenum magnification_filter = GL_LINEAR, minification_filter = GL_LINEAR_MIPMAP_LINEAR;
        GLenum wrap_s = GL_REPEAT, wrap_t = GL_REPEAT;
        glm::vec4 border_color = {1,1,1,1};
        GLfloat max_anisotropy = 1.0f;
    public:
        Texture(){
            glGenTextures(1, &texture);
        };
        ~Texture(){destroy();}

        //Delete copy constructor and assignment operation
        //This is important for Class that follow the RAII pattern since we destroy the underlying OpenGL object in deconstruction
        //So if we copied the object, one of them can destroy the object(s) while the other still thinks they are valid.
        Texture(Texture const &) = delete;
        Texture &operator=(Texture const &) = delete;

        void create(const void *data, glm::ivec2 size,bool generate_mipmap = true);

        void draw();
        void destroy();

        // Load an image from a file
        glm::ivec2 loadImage(const char* filename, bool generate_mipmap = true);;

        void checkerBoard();
    };
}



#endif //GRAPHICS_TEXTURE_H
