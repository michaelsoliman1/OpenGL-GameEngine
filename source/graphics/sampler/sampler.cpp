//
// Created by ecs on 1/3/2021.
//

#include "sampler.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../utils/stb/stb_image.h"

void xGame::Sampler::create(const void *data, glm::ivec2 size, bool generate_mipmap) {

}

void xGame::Sampler::destroy() {

    glDeleteSamplers(1, &sampler);
    for(auto& [name, texture]: textures){
        glDeleteTextures(1, &texture);
    }
    textures.clear();
}

void xGame::Sampler::drawNode(const std::shared_ptr<Transform> &node, const glm::mat4 &parent_transform_matrix) {
    glm::mat4 transform_matrix = parent_transform_matrix * node->to_mat4();
    if(node->mesh.has_value()){
        if(auto mesh_it = meshes.find(node->mesh.value()); mesh_it != meshes.end()) {
            GLuint texture = 0;
            if(auto tex_it = textures.find(node->texture); tex_it != textures.end())
                texture = tex_it->second;
            glBindTexture(GL_TEXTURE_2D, texture);
            shader.set("tint", node->tint);
            shader.set("transform", transform_matrix);
            mesh_it->second->draw();
        }
    }
    for(auto& [name, child]: node->children){
        drawNode(child, transform_matrix);
    }
}

void xGame::Sampler::onDraw(double deltaTime) {
    camera_controller.update(deltaTime);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindSampler(0, sampler);

    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, magnification_filter);
    glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, minification_filter);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, wrap_s);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, wrap_t);
    glSamplerParameterfv(sampler, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(border_color));
    glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);

    glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);

    //drawNode(*root, camera.getVPMatrix());
}