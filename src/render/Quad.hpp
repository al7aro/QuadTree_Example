#pragma once

#include <array>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace FT {

    struct Vertex
    {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 tex_coords;
    };

    struct Quad
    {
		glm::vec2 pos;
		glm::vec2 size;
		glm::vec4 col;
        Quad(const glm::vec2& p_pos, const glm::vec2& p_size, const glm::vec4& p_col)
            : pos(p_pos), size(p_size), col(p_col)
        {}
        virtual ~Quad() {}
        virtual bool Contains(const glm::vec2& p) const
        {
            if (size.x <= 0.0 || size.y <= 0.0)
                return (false);
            if (pos.x + size.x/2.0f >= p.x &&
                pos.y + size.y/2.0f >= p.y &&
                pos.x - size.x/2.0f <= p.x &&
                pos.y - size.y/2.0f <= p.y)
                return (true);
            return (false);
        }

        static std::array<Vertex, 4> gen_vertices(
            glm::vec2 pos = glm::vec2(0.0),
            glm::vec2 size = glm::vec2(1.0),
            glm::vec4 col = glm::vec4(1.0))
        {
            size /= glm::vec2(2.0);
            std::array<Vertex, 4> ret;
            /* BOT LEFT VERTEX */
            ret[0].position = glm::vec3(pos.x - size.x, pos.y - size.y, 0.0);
            ret[0].color = col;
            ret[0].tex_coords = glm::vec2(0.0, 0.0);
            /* BOT RIGHT VERTEX */
            ret[1].position = glm::vec3(pos.x + size.x, pos.y - size.y, 0.0);
            ret[1].color = col;
            ret[1].tex_coords = glm::vec2(1.0, 0.0);
            /* TOP RIGHT VERTEX */
            ret[2].position = glm::vec3(pos.x + size.x, pos.y + size.y, 0.0);
            ret[2].color = col;
            ret[2].tex_coords = glm::vec2(1.0, 1.0);
            /* TOP LEFT VERTEX */
            ret[3].position = glm::vec3(pos.x - size.x, pos.y + size.y, 0.0);
            ret[3].color = col;
            ret[3].tex_coords = glm::vec2(0.0, 1.0);
            return (ret);
        }

        static std::array<unsigned int, 6> gen_indices(unsigned int offset = 0)
        {
            std::array<unsigned int, 6> ret = {
                0 + offset, 1 + offset, 2 + offset,
                2 + offset, 3 + offset, 0 + offset
            };
            return (ret);
        }
    };

}