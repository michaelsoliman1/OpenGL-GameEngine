//
// Created by michael on ٢‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_MATERIAL_H
#define GRAPHICS_MATERIAL_H

#include "../graphics/shader/shader.hpp"
#include "../render_state/RenderState.h"
#include "../texture/texture.h"

namespace xGame{
    class Material {
    public:
        Material(){
            program = new xGame::ShaderProgram();
            renderState = new xGame::RenderState();
            texture = new xGame::Texture();
            hasTexture = false;
        }

        //we can pass a RenderState pointer here with a predefined data!! don't know if that's right or not
        //for now i'll just pass the parameters through the constructor
//        Clang-Tidy: Single-argument constructors must be marked explicit
//        to avoid unintentional implicit conversions!!!
        Material(bool enableDepthTesting, bool enableFaceCulling = false,bool enableBlending = false, bool _hasTexture = false){
            program = new xGame::ShaderProgram();
            texture = new xGame::Texture();
            renderState = new xGame::RenderState(enableDepthTesting, enableFaceCulling, enableBlending);
            hasTexture = _hasTexture;
        }
        ~Material(){
            delete program;
            delete renderState;
        }
        xGame::ShaderProgram *program;
        xGame::RenderState *renderState;
        xGame::Texture * texture;

        bool hasTexture;

        glm::vec4 tint = glm::vec4(1,1,1,1);
    };


}

#endif //GRAPHICS_MATERIAL_H
