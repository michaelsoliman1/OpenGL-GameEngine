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
        glm::vec3 tint = glm::vec3(1,1,1);

        glm::vec3 albedoTint = {1,1,1};
        glm::vec3 specularTint = {1,1,1};
        glm::vec3 emissiveTint = {0.5,0.5,0.5};
        glm::vec2 roughnessRange = {0.5,0.5};


        //TODO
        //create a RenderState object and pass it
        //and how can i make it dynamic? the user creates it with the settings he need right away (is passing all the the options in the constructor a good way?
        // i can create a struct with parameters
        explicit Material(std::unordered_map<xGame::TextureType, xGame::Texture*> _textures = {},bool _transparent = false,bool enableDepthTesting = true, bool enableFaceCulling = false,bool enableBlending = false){
            //TODO--add shader parameter
            program = new xGame::ShaderProgram();
            sampler = new xGame::Sampler();
            //TODO--add default map for texture
            textures = _textures;
            transparent = _transparent;
            //TODO--add renderState object as a paramater
            renderState = new xGame::RenderState(transparent, enableDepthTesting, enableFaceCulling, enableBlending);
        }
        void destroy() const{
            delete sampler;
        }
        ~Material(){
            destroy();
        }
    };


}

#endif //GRAPHICS_MATERIAL_H
