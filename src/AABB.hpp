#pragma once

#include <glm/glm.hpp>

namespace FT {

    /* AXIS ALIGNED BOUNDING BOX */
    struct AABB
    {
        glm::vec2 pos;
        float half_size;

        AABB(const glm::vec2& p_pos)
            : pos(p_pos), half_size(0.0)
        {
        }
        AABB(const glm::vec2& p_pos, float p_half_size)
            : pos(p_pos), half_size(p_half_size)
        {
        }

        bool Contains(const glm::vec2& p) const
        {
            if (half_size <= 0.0)
                return (false);
            if (pos.x + half_size >= p.x &&
                pos.y + half_size >= p.y &&
                pos.x - half_size <= p.x &&
                pos.y - half_size <= p.y)
                return (true);
            return (false);
        }

        bool Contains(const AABB& o) const
        {
            glm::vec2 NW = glm::vec2(pos.x - half_size, pos.y + half_size);
            glm::vec2 NE = glm::vec2(pos.x + half_size, pos.y + half_size);
            glm::vec2 SW = glm::vec2(pos.x - half_size, pos.y - half_size);
            glm::vec2 SE = glm::vec2(pos.x + half_size, pos.y - half_size);

            if (Contains(NW) && Contains(NE) && Contains(SW) && Contains(SE))
                return (true);
            return (false);
        }

        bool Intersects(const AABB& o) const
        {
            glm::vec2 o_NW = glm::vec2(o.pos.x - o.half_size, o.pos.y + o.half_size);
            glm::vec2 o_NE = glm::vec2(o.pos.x + o.half_size, o.pos.y + o.half_size);
            glm::vec2 o_SW = glm::vec2(o.pos.x - o.half_size, o.pos.y - o.half_size);
            glm::vec2 o_SE = glm::vec2(o.pos.x + o.half_size, o.pos.y - o.half_size);
            glm::vec2 NW = glm::vec2(pos.x - half_size, pos.y + half_size);
            glm::vec2 NE = glm::vec2(pos.x + half_size, pos.y + half_size);
            glm::vec2 SW = glm::vec2(pos.x - half_size, pos.y - half_size);
            glm::vec2 SE = glm::vec2(pos.x + half_size, pos.y - half_size);

            if (Contains(o_NW) || Contains(o_NE) || Contains(o_SW) || Contains(o_SE))
                return (true);
            if (o.Contains(NW) || o.Contains(NE) || o.Contains(SW) || o.Contains(SE))
                return (true);
            return (false);
        }
    };

}