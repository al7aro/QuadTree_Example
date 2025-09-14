#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Quad.hpp"
#include "buffers/VAO.hpp"
#include "buffers/VBO.hpp"
#include "buffers/IBO.hpp"

namespace FT {

    class Renderer2D
    {
    private:
        static constexpr unsigned int BATCH_SIZE = sizeof(Vertex) * 4 * 1000; // 4000 vertices -> 1000 quads per batch
        // static constexpr unsigned int BATCH_SIZE = sizeof(Vertex) * 4; // 4 vertices -> 1 quad per batch
        static constexpr unsigned int TEXTURE_SLOTS = 8;

        VAO _vao;
        VBO _vbo;
        IBO _ibo;
        unsigned int _index_count;
        unsigned int _vertex_count;
        unsigned int _num_of_batches;
        
    public:
        Renderer2D()
            : _vao(), _vbo(BATCH_SIZE), _ibo(BATCH_SIZE), _index_count(0), _vertex_count(0), _num_of_batches(0)
        {
            _vao.AddVBO(_vbo);
            _vao.AddIBO(_ibo);
        }

        void Begin()
        {
            _num_of_batches = 0;
        }

        void End()
        {
		    Flush();
        }

        void DrawQuad(const glm::vec2& pos = glm::vec2(0.0),
                      const glm::vec2& size = glm::vec2(1.0),
                      const glm::vec4& col = glm::vec4(1.0))
        {
            if (sizeof(Vertex) * (_vertex_count + 4) > BATCH_SIZE)
            {
                Flush();
            }
            std::array<Vertex, 4> vertices = Quad::gen_vertices(pos, size, col);
            std::array<unsigned int, 6> indices = Quad::gen_indices(_vertex_count);
            _vbo.AddData(vertices.data(), sizeof(vertices));
            _ibo.AddData(indices.data(), sizeof(indices));
            _index_count += 6;
            _vertex_count += 4;
        }

        void Flush()
        {
            _vao.Bind();
            glDrawElements(GL_TRIANGLES, _index_count, GL_UNSIGNED_INT, 0);
            _num_of_batches++;
            Clear();
        }

        void Clear()
        {
            _vbo.Clear();
            _ibo.Clear();
            _index_count = 0;
            _vertex_count = 0;
        }

        unsigned int GetNumOfBatches() const
        {
            return (_num_of_batches);
        }
    };

}