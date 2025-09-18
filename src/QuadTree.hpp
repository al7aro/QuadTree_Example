#pragma once

#include <utility>
#include <functional>

#include <glm/glm.hpp>

#include "AABB.hpp"

namespace FT {

    template <typename T>
    class QuadTree
    {
    public:
        enum DirectionIndex
        {
            NORTH_WEST = 0,
            NORTH_EAST = 1,
            SOUTH_WEST = 2,
            SOUTH_EAST = 3
        };
    private:
        AABB _bb;
        std::vector<std::pair<AABB, T> > _data;

        QuadTree* _nodes[4];

        size_t _max_depth;
        size_t _current_depth;
        bool _subdivided;
    public:
        QuadTree(AABB bounding_box, size_t max_depth = 1024, size_t current_depth = 0)
            : _bb(bounding_box), _data(),
            _max_depth(max_depth), _current_depth(current_depth), _subdivided(false)
        {
            for (int i = 0; i < 4; i++)
                _nodes[i] = nullptr;
        }

        ~QuadTree()
        {
            for (int i = 0; i < 4; i++)
            {
                if (_nodes[i])
                {
                    delete _nodes[i];
                }
            }
        }

        void Subdivide()
        {
            /* TOP LEFT */
            AABB bb = AABB{glm::vec2(_bb.pos.x - _bb.half_size/2.0f, _bb.pos.y + _bb.half_size/2.0f), _bb.half_size/2.0f};
            _nodes[NORTH_WEST] = new QuadTree(bb, _max_depth, _current_depth + 1);
            /* TOP RIGHT */
            bb = AABB{glm::vec2(_bb.pos.x + _bb.half_size/2.0f, _bb.pos.y + _bb.half_size/2.0f), _bb.half_size/2.0f};
            _nodes[NORTH_EAST] = new QuadTree(bb, _max_depth, _current_depth + 1);
            /* BOTTOM LEFT */
            bb = AABB{glm::vec2(_bb.pos.x - _bb.half_size/2.0f, _bb.pos.y - _bb.half_size/2.0f), _bb.half_size/2.0f};
            _nodes[SOUTH_WEST] = new QuadTree(bb, _max_depth, _current_depth + 1);
            /* BOTTOM RIGHT */
            bb = AABB{glm::vec2(_bb.pos.x + _bb.half_size/2.0f, _bb.pos.y - _bb.half_size/2.0f), _bb.half_size/2.0f};
            _nodes[SOUTH_EAST] = new QuadTree(bb, _max_depth, _current_depth + 1);
            _subdivided = true;
        }

        void Insert(const glm::vec2& pos, const T& data)
        {
            if (!_subdivided && _current_depth <= _max_depth)
                Subdivide();
            for (int i = 0; i < 4; i++)
            {
                if (!_nodes[i])
                    continue ;
                if (_nodes[i]->_bb.Contains(pos))
                {
                    _nodes[i]->Insert(pos, data);
                    break ;
                }
            }
            if (_current_depth == _max_depth)
                _data.push_back(std::make_pair(AABB(pos), data));
        }

        /* FUNCTION THAT DOES NOT RETURN A VECTOR BUT INSTEAD APPLIES A FUNCTION TO ALL MATCHES */
        int QueryMap(const AABB& bb, std::function<void(const T&)> callback)
        {
            int ret = 0;
            if (bb.Intersects(_bb))
            {
                for (auto& d : _data)
                {
                    if (bb.Contains(d.first))
                    {
                        if (bb.Contains(d.second.pos))
                        {
                            callback(d.second);
                            ret++;
                        }
                    }
                }
                if (_subdivided)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        ret += _nodes[i]->QueryMap(bb, callback);
                    }
                }
            }
            return (ret);
        }

        /* Returns all object inside bb */
        std::vector<T> QueryRange(const AABB& bb)
        {
            std::vector<T> ret;

            if (bb.Intersects(_bb))
            {
                for (auto& d : _data)
                {
                    if (bb.Contains(d.first))
                        ret.push_back(d.second);
                }
                if (_subdivided)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        std::vector<T> sub_ret =  _nodes[i]->QueryRange(bb);
                        ret.insert(ret.end(), sub_ret.begin(), sub_ret.end());
                    }
                }
            }

            return (ret);
        }
    };

}