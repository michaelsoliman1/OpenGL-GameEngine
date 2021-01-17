//
// Created by michael on ٢‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_MATERIAL_H
#define GRAPHICS_MATERIAL_H

#include <unordered_map>
#include <utility>
#include <any>

#include "../graphics/shader/shader.hpp"
#include "../render_state/RenderState.h"
#include "../texture/texture.h"
#include "../sampler/sampler.h"
#include "../../utils/enums.h"

namespace xGame{
    class Material {
    public:
        ShaderProgram *program;
        std::unordered_map<std::string , std::any> properties;
        std::unordered_map<TextureType, Texture*> textures;
        RenderState *renderState;

        // TODO? do i need a sampler for each texture ?
        // if yes? use std::unordered_map<TextureType, std::pair<Texture*, Sampler*>>
        Sampler* sampler;

        explicit Material(ShaderProgram* _program = nullptr, std::unordered_map<TextureType, Texture*> _textures = {}, std::unordered_map<std::string , std::any> _properties = {}, Sampler* _sampler = nullptr, RenderState* _renderState = nullptr){
            //TODO--add shader object as parameter
            program = new xGame::ShaderProgram();
            _sampler== nullptr ? sampler = new xGame::Sampler() : sampler = _sampler;
            _renderState == nullptr ? renderState = new xGame::RenderState() : renderState = _renderState;
            //TODO--add default map for texture
            textures = std::move(_textures);
            properties = std::move(_properties);
        }
        void destroy() const{

        }
        ~Material(){
            destroy();
        }
    };


}

#endif //GRAPHICS_MATERIAL_H
