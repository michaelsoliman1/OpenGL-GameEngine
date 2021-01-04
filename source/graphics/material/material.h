//
// Created by michael on ٢‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_MATERIAL_H
#define GRAPHICS_MATERIAL_H

#include "../graphics/shader/shader.hpp"
#include "../render_state/RenderState.h"
#include "../texture/texture.h"
#include "../sampler/sampler.h"

namespace xGame{
    class Material {
    public:
        //we can pass a RenderState pointer here with a predefined data!! don't know if that's right or not
        //for now i'll just pass the parameters through the constructor
//        Clang-Tidy: Single-argument constructors must be marked explicit
//        to avoid unintentional implicit conversions!!!
        Material(xGame::Texture* _texture = nullptr ,bool enableDepthTesting = true, bool enableFaceCulling = false,bool enableBlending = false){
            program = new xGame::ShaderProgram();
            sampler = new xGame::Sampler();
            (_texture== nullptr) ? texture = new xGame::Texture() : texture = _texture;
            renderState = new xGame::RenderState(enableDepthTesting, enableFaceCulling, enableBlending);
        }
        ~Material(){
            delete program;
            delete renderState;
        }
        xGame::ShaderProgram *program;
        xGame::RenderState *renderState;
        xGame::Texture * texture;
        xGame::Sampler* sampler;

//        bool hasTexture;

        glm::vec4 tint = glm::vec4(0.94,0.94,0.9,1.0);
    };


}

#endif //GRAPHICS_MATERIAL_H
