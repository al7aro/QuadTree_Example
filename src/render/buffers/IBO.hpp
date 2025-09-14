#pragma once

#include <glad/glad.h>

#include "../Vertex.hpp"

namespace FT {

    class IBO
    {
    private:
        unsigned int _id;
        size_t _max_size;
        size_t _offset;
    public:
        IBO(unsigned int size = 1024)
            : _id(0), _max_size(size), _offset(0)
        {
            glGenBuffers(1, &_id);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, _max_size, nullptr, GL_DYNAMIC_DRAW);
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
        void Bind(unsigned int vao)
        {
        	glVertexArrayElementBuffer(vao, _id);
        }
    };

}