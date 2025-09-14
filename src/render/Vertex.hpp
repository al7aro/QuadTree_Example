#pragma once

#include <glm/glm.hpp>

namespace FT {

    struct Vertex
    {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 tex_coords;
    };

}