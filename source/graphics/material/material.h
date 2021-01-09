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
        xGame::ShaderProgram *program;
        xGame::RenderState *renderState;
        xGame::Texture * texture;
        xGame::Sampler* sampler;
        glm::vec4 tint = glm::vec4(0.94,0.94,0.9,0.5);
        bool transparent;

        //TODO?
        //we can pass a RenderState pointer here with a predefined data!! don't know if that's right or not.
        //and how can i make it dynamic? the user creates it with the settings he need right away (is passing all the the options in the constructor a good way?
        //for now i'll just pass the parameters through the constructor
//        Clang-Tidy: Single-argument constructors must be marked explicit
//        to avoid unintentional implicit conversions!!!
        Material(xGame::Texture* _texture = nullptr,bool _transparent = false,bool enableDepthTesting = true, bool enableFaceCulling = false,bool enableBlending = false){
            program = new xGame::ShaderProgram();
            sampler = new xGame::Sampler();
            (_texture== nullptr) ? texture = new xGame::Texture() : texture = _texture;
            transparent = _transparent;
            renderState = new xGame::RenderState(transparent, enableDepthTesting, enableFaceCulling, enableBlending);
        }
        void destroy() const{
            delete program;
            delete renderState;
            delete sampler;
            delete texture;
        }
        ~Material(){
            destroy();
        }
    };


}

#endif //GRAPHICS_MATERIAL_H
