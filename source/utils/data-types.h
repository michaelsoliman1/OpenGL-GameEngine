//
// Created by michael on ٢٠‏/١٢‏/٢٠٢٠.
//

#ifndef GRAPHICS_DATA_TYPES_H
#define GRAPHICS_DATA_TYPES_H

#include <glm/glm.hpp>

namespace xGame {
    // Since we may want to store colors in bytes instead of floats for efficiency,
    // we are creating our own 32-bit R8G8B8A8 Color data type with the default GLM precision
    typedef glm::vec<4, glm::uint8, glm::defaultp> Color;
}

#endif //GRAPHICS_DATA_TYPES_H
