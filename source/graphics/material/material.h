//
// Created by michael on ٢‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_MATERIAL_H
#define GRAPHICS_MATERIAL_H

#include <unordered_map>
#include <utility>

#include "../graphics/shader/shader.hpp"
#include "../render_state/RenderState.h"
#include "../texture/texture.h"
#include "../sampler/sampler.h"
#include "../../utils/enums.h"

namespace xGame{
    class Material {
    public:
        xGame::ShaderProgram *program;
        std::unordered_map<xGame::TextureType, xGame::Texture*> textures;
        xGame::Sampler* sampler;
        xGame::RenderState *renderState;

        //TODO add them in map or dict
        glm::vec3 tint = glm::vec3(1,1,1);
        glm::vec3 albedoTint = {1,1,1};
        glm::vec3 specularTint = {1,1,1};
        glm::vec3 emissiveTint = {0.2,0.2,0.2};
        glm::vec2 roughnessRange = {0.5,0.5};


        explicit Material(xGame::ShaderProgram* _program = nullptr, std::unordered_map<xGame::TextureType, xGame::Texture*> _textures = {}, xGame::Sampler* _sampler = nullptr, xGame::RenderState* _renderState = nullptr){
            //TODO--add shader object as parameter
            program = new xGame::ShaderProgram();
            _sampler== nullptr ? sampler = new xGame::Sampler() : sampler = _sampler;
            _renderState == nullptr ? renderState = new xGame::RenderState() : renderState = _renderState;
            //TODO--add default map for texture
            textures = std::move(_textures);
        }
        void destroy() const{

        }
        ~Material(){
            destroy();
        }
    };


}

#endif //GRAPHICS_MATERIAL_H
