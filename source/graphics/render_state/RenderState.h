//
// Created by michael on ٢‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_RENDERSTATE_H
#define GRAPHICS_RENDERSTATE_H


#include <glad/gl.h>

namespace xGame {
    class RenderState {
    public:
        bool depthTesting;
        bool faceCulling;

        RenderState() {
            depthTesting = true;
            faceCulling = false;
        };

        RenderState(bool _enableDepthTesting, bool _enableFaceCulling = false){
            depthTesting = _enableDepthTesting;
            faceCulling = _enableFaceCulling;
        }

        void setRenderState() const {
            if (depthTesting) enableDepthTesting();
            else glDisable(GL_DEPTH_TEST);
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
    };
}



#endif //GRAPHICS_RENDERSTATE_H
