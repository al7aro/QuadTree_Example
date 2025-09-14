#pragma once

#include <glad/glad.h>

#include "../Vertex.hpp"

namespace FT {

    class VBO
    {
    private:
        unsigned int _id;
        unsigned int _bindingindex;
        size_t _max_size;
        size_t _offset;
    public:
        VBO(unsigned int size = 1024)
            : _id(0), _bindingindex(0), _max_size(size), _offset(0)
        {
            glGenBuffers(1, &_id);
            glBindBuffer(GL_ARRAY_BUFFER, _id);
            glBufferData(GL_ARRAY_BUFFER, _max_size, nullptr, GL_STATIC_DRAW);
        }
        void Clear()
        {
            _offset = 0;
        }
        void AddData(const void* data, unsigned int size)
        {
            if (_offset + size > _max_size)
                return ;
            glNamedBufferSubData(_id, _offset, size, data);
            _offset += size;
        }
        void BindAttrib(unsigned int bindingindex, unsigned int vao, unsigned int stride = sizeof(Vertex))
        {
            _bindingindex = bindingindex;
        	glVertexArrayVertexBuffer(vao, bindingindex, _id, 0, stride);
        }
    };

}