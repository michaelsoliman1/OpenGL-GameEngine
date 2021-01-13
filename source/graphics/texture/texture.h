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

    public:
        const char *filename;

        Texture(const char *_filename = nullptr){
            filename = _filename;
        };
        ~Texture(){destroy();}

        //Delete copy constructor and assignment operation
        //This is important for Class that follow the RAII pattern since we destroy the underlying OpenGL object in deconstruction
        //So if we copied the object, one of them can destroy the object(s) while the other still thinks they are valid.
        Texture(Texture const &) = delete;
        Texture &operator=(Texture const &) = delete;

        void create(const void *data, glm::ivec2 size,bool generate_mipmap = true);

        void setActive(GLenum texture);
        void bind();
        void destroy();

        GLuint getTexture(){return texture;};

        // Load an image from a file
        glm::ivec2 load( bool generate_mipmap = true);;

        glm::ivec2 checkerBoard();
    };
}



#endif //GRAPHICS_TEXTURE_H
