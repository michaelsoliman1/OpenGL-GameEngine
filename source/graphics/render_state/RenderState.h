//
// Created by michael on ٢‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_RENDERSTATE_H
#define GRAPHICS_RENDERSTATE_H


#include <glad/gl.h>
#include <glm/fwd.hpp>
#include <glm/detail/type_vec4.hpp>

namespace xGame {
    class RenderState {
    public:
        bool depthTesting;
        bool faceCulling;
        bool blending;


        RenderState() {
            depthTesting = true;
            faceCulling = false;
            blending = false;

        };

        RenderState(bool _enableDepthTesting, bool _enableFaceCulling = false, bool _enableBlending = false){
            depthTesting = _enableDepthTesting;
            faceCulling = _enableFaceCulling;
            blending = _enableBlending;

        }

        void setRenderState() const {
            if (depthTesting) enableDepthTesting();
            else glDisable(GL_DEPTH_TEST);
            if(faceCulling) enableFaceCulling();
            else glDisable(GL_CULL_FACE);
            if(faceCulling) enableFaceCulling();
            else glDisable(GL_CULL_FACE);
        }

        // TODO - add parameters
        static void enableDepthTesting() {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            glClearDepth(1.0f);
            glDepthMask(true);
            glColorMask(true, true, true, true);
        };
        // TODO - add parameters
        static void enableFaceCulling(){
            glCullFace(GL_BACK);
            glFrontFace(GL_CCW);
        }

        static void enableBlending(){
            GLenum blend_equation = GL_FUNC_ADD;
            GLenum blend_source_factor = GL_SRC_ALPHA, blend_destination_factor = GL_ONE_MINUS_SRC_ALPHA;
            glm::vec4 blend_constant_color = {1.0f,1.0f,1.0f,1.0f};
            // The blending formula has the following form: (source_factor * source) operation (destination_factor * destination).
            // The operation is specified by the blend equation function.
            // The possible values are:
            //  -   GL_FUNC_ADD: the operation is "+".
            //  -   GL_FUNC_SUBTRACT: the operation is "-".
            //  -   GL_FUNC_REVERSE_SUBTRACT: the operation is "-" but the operands are reversed.
            //  -   GL_MIN: the operation picks the minimum value among the 2 operands.
            //  -   GL_MAX: the operation picks the maximum value among the 2 operands.
            glBlendEquation(blend_equation);
            // This function specifies the source of the factors for each operand.
            // the possible values are:
            //  -   GL_ZERO
            //  -   GL_ONE
            //  -   GL_SRC_COLOR
            //  -   GL_ONE_MINUS_SRC_COLOR
            //  -   GL_DST_COLOR
            //  -   GL_ONE_MINUS_DST_COLOR
            //  -   GL_SRC_ALPHA
            //  -   GL_ONE_MINUS_SRC_ALPHA
            //  -   GL_DST_ALPHA
            //  -   GL_ONE_MINUS_DST_ALPHA
            //  -   GL_CONSTANT_COLOR
            //  -   GL_ONE_MINUS_CONSTANT_COLOR
            //  -   GL_CONSTANT_ALPHA
            //  -   GL_ONE_MINUS_CONSTANT_ALPHA
            glBlendFunc(blend_source_factor, blend_destination_factor);
            // In case you're using any of the factors that use the constant color, you need to define it via the glBlendColor function.
            glBlendColor(blend_constant_color.r, blend_constant_color.g, blend_constant_color.b, blend_constant_color.a);
        }
    };
}



#endif //GRAPHICS_RENDERSTATE_H
