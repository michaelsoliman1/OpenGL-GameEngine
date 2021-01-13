//
// Created by michael on ٢‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_MATERIAL_H
#define GRAPHICS_MATERIAL_H

#include <unordered_map>

#include "../graphics/shader/shader.hpp"
#include "../render_state/RenderState.h"
#include "../texture/texture.h"
#include "../sampler/sampler.h"
#include "../../utils/enums.h"

namespace xGame{
    class Material {
    public:
        xGame::ShaderProgram *program;

        xGame::RenderState *renderState;
        std::unordered_map<xGame::TextureType, xGame::Texture*> textures;

        xGame::Sampler* sampler;
        bool transparent;
        glm::vec4 tint = glm::vec4(0.94,0.94,0.9,0.5);

        glm::vec3 albedoTint = {0, 0, 0};
        glm::vec3 specularTint = {0.4, 0.4, 0.4};
        glm::vec3 emissiveTint = {1, 1, 1};
        glm::vec2 roughnessRange = {20,30};


        //TODO
        //create a RenderState object and pass it
        //and how can i make it dynamic? the user creates it with the settings he need right away (is passing all the the options in the constructor a good way?
        // i can create a struct with parameters
        explicit Material(std::unordered_map<xGame::TextureType, xGame::Texture*> _textures = {},bool _transparent = false,bool enableDepthTesting = true, bool enableFaceCulling = false,bool enableBlending = false){
            program = new xGame::ShaderProgram();
            sampler = new xGame::Sampler();
            //TODO add default map for texture
            (_textures.empty()) ? textures = {} : textures = _textures;
            transparent = _transparent;
            renderState = new xGame::RenderState(transparent, enableDepthTesting, enableFaceCulling, enableBlending);
        }
        void destroy() const{
            delete program;
            delete renderState;
            delete sampler;
        }
        ~Material(){
            destroy();
        }
    };


}

#endif //GRAPHICS_MATERIAL_H
