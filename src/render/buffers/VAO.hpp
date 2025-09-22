#pragma once

#include <glad/glad.h>

#include "../Quad.hpp"
#include "VBO.hpp"
#include "IBO.hpp"

namespace FT {

    class VAO
    {
    private:
        unsigned int _id;
    public:
        VAO()
        {
            glGenVertexArrays(1, &_id);
            glBindVertexArray(_id);
        }
        void AddVBO(VBO & vbo, unsigned int bindingindex = 0)
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
            /* TEX ID */
            glEnableVertexArrayAttrib(_id, 3);
            glVertexArrayAttribBinding(_id, 3, bindingindex);
            glVertexArrayAttribFormat(_id, 3, 1, GL_FLOAT, GL_FALSE, offsetof(Vertex, tex_id));
        }
        void AddIBO(IBO & ibo)
        {
            ibo.Bind(_id);
        }
        void AddVBO(VBO & vbo, unsigned int bindingindex, unsigned int att_id,
            unsigned int size, unsigned int type, unsigned int normalized, unsigned int offset, unsigned int stride)
        {
            vbo.BindAttrib(bindingindex, _id, stride);
            glEnableVertexArrayAttrib(_id, att_id);
            glVertexArrayAttribBinding(_id, att_id, bindingindex);
            glVertexArrayAttribFormat(_id, att_id, size, type, normalized, offset);
        }
        void Bind() const
        {
            glBindVertexArray(_id);
        }
    };

}