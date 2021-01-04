//
// Created by michael on ٣‏/١‏/٢٠٢١.
//

#include "texture.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../utils/stb/stb_image.h"


void xGame::Texture::create(const void *data, glm::ivec2 size, bool generate_mipmap) {

    //Bind the texture such that we upload the image data to its storage
    glBindTexture(GL_TEXTURE_2D, texture);
    //Set Unpack Alignment to 4-byte (it means that each row takes multiple of 4 bytes in memory)
    //Note: this is not necessary since:
    //- Alignment is 4 by default
    //- Alignment of 1 or 2 will still work correctly but 8 may cause problems
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    //Send data to texture
    //NOTE: the internal format is set to GL_RGBA8 so every pixel contains 4 bytes, one for each channel
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //Generate versions of the texture at smaller level of details (useful for filtering)
    if(generate_mipmap) glGenerateMipmap(GL_TEXTURE_2D);
}

void xGame::Texture::draw() {

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnification_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minification_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(border_color));
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
}

void xGame::Texture::destroy() {
    glDeleteTextures(1, &texture);
}

glm::ivec2 xGame::Texture::loadImage(const char *filename, bool generate_mipmap) {
    glm::ivec2 size;
    int channels;
    //Since OpenGL puts the texture origin at the bottom left while images typically has the origin at the top left,
    //We need to till stb to flip images vertically after loading them
    stbi_set_flip_vertically_on_load(true);
    //Load image data and retrieve width, height and number of channels in the image
    //The last argument is the number of channels we want and it can have the following values:
    //- 0: Keep number of channels the same as in the image file
    //- 1: Grayscale only
    //- 2: Grayscale and Alpha
    //- 3: RGB
    //- 4: RGB and Alpha
    //Note: channels (the 4th argument) always returns the original number of channels in the file
    unsigned char* data = stbi_load(filename, &size.x, &size.y, &channels, 4);
    if(data == nullptr){
        std::cerr << "Failed to load image: " << filename << std::endl;
        return {0, 0};
    }

    this->create(data, size, generate_mipmap);
    stbi_image_free(data); //Free image data after uploading to GPU
    return size;
}

void xGame::Texture::checkerBoard() {
    glm::ivec2 size = {256,256};
    glm::ivec2 patternSize = {128,128};
    xGame::Color color1 =  {255, 255, 255, 255};
    xGame::Color color2 =  {16, 16, 16, 255};

    auto *data = new xGame::Color[size.x * size.y];
    int ptr = 0;
    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            data[ptr++] = ((x/patternSize.x)&1)^((y/patternSize.y)&1)?color1:color2;
        }
    }
    create(data, size);
    delete[] data;
}
