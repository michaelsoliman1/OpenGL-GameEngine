//
// Created by michael on ٢٩‏/١٢‏/٢٠٢٠.
//

#ifndef GRAPHICS_ENUMS_H
#define GRAPHICS_ENUMS_H

namespace xGame {
    // An enum for the camera projection type
    enum struct CameraType {
        Orthographic,
        Perspective
    };
    // An enum for light types
    enum class LightType {
        DIRECTIONAL,
        POINT,
        SPOT
    };

    enum struct TextureType {
        ALBEDO,
        SPECULAR,
        AMBIENT,
        ROUGHNESS,
        EMISSIVE
    };
}

#endif //GRAPHICS_ENUMS_H
