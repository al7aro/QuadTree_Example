#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace FT {

    struct Vertex
    {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 tex_coords;
    };

    class VBO
    {
    private:
        unsigned int _id;
        unsigned int _bindingindex;
        size_t _size;
        size_t _offset;
    public:
        VBO(unsigned int size = 1024)
            : _id(0), _bindingindex(0), _size(size), _offset(0)
        {
            glGenBuffers(1, &_id);
            glBindBuffer(GL_ARRAY_BUFFER, _id);
            glBufferData(GL_ARRAY_BUFFER, _size, nullptr, GL_STATIC_DRAW);
        }
        void Clear()
        {
            _offset = 0;
        }
        void AddData(const void* data, unsigned int size)
        {
            glNamedBufferSubData(_id, _offset, size, data);
            _offset += _size;
        }
        void BindAttrib(unsigned int bindingindex, unsigned int vao, unsigned int stride = sizeof(Vertex))
        {
            _bindingindex = bindingindex;
        	glVertexArrayVertexBuffer(vao, bindingindex, _id, 0, stride);
        }
    };

    class VAO
    {
    private:
        unsigned int _id;
        std::vector<VBO> _vbo;
    public:
        VAO()
        {
            glGenVertexArrays(1, &_id);
            glBindVertexArray(_id);
        }
        void AddVBO(VBO & vbo, unsigned int bindingindex)
        {
            vbo.BindAttrib(bindingindex, _id);
            /* POSITION */
            glEnableVertexArrayAttrib(_id, 0);
            glVertexArrayAttribBinding(_id, 0, bindingindex);
            glVertexArrayAttribFormat(_id, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
            /* COLOR */
            glEnableVertexArrayAttrib(_id, 1);
            glVertexArrayAttribBinding(_id, 1, bindingindex);
            glVertexArrayAttribFormat(_id, 1, 4, GL_FLOAT, GL_FALSE, offsetof(Vertex, color));
            /* TEX COORDS */
            glEnableVertexArrayAttrib(_id, 2);
            glVertexArrayAttribBinding(_id, 2, bindingindex);
            glVertexArrayAttribFormat(_id, 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, tex_coords));
            _vbo.push_back(vbo);
        }
        void AddVBO(VBO & vbo, unsigned int bindingindex, unsigned int att_id,
            unsigned int size, unsigned int type, unsigned int normalized, unsigned int offset, unsigned int stride)
        {
            vbo.BindAttrib(bindingindex, _id, stride);
            glEnableVertexArrayAttrib(_id, att_id);
            glVertexArrayAttribBinding(_id, att_id, bindingindex);
            glVertexArrayAttribFormat(_id, att_id, size, type, normalized, offset);
            _vbo.push_back(vbo);
        }
        void Bind() const
        {
		    glBindVertexArray(_id);
        }
    };

}