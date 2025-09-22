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
        Shader _shader;
        std::array<Texture2D, 8> _textures;
        unsigned int _index_count;
        unsigned int _vertex_count;
        unsigned int _tex_count;
        unsigned int _num_of_batches;
        
    public:
        Renderer2D()
            : _vao(), _vbo(BATCH_SIZE), _ibo(BATCH_SIZE), _shader(), _index_count(0), _vertex_count(0), _tex_count(0),
            _num_of_batches(0)
        {
            _vao.AddVBO(_vbo);
            _vao.AddIBO(_ibo);
        }

        void Begin(const Shader& sh)
        {
            _shader = sh;
            _num_of_batches = 0;
        }

        void End()
        {
		    Flush();
        }


        void DrawQuad(const Quad& quad)
        {
            DrawQuad(quad.pos, quad.size, quad.col, quad.tex);
        }

        void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& col, const Texture2D& tex = Texture2D())
        {
            float tex_id = -1.0;
            if (sizeof(Vertex) * (_vertex_count + 4) > BATCH_SIZE || _tex_count >= 8)
            {
                Flush();
            }
            if (tex.GetId())
            {
                // Check if that texture is already in use in this renderer
                for (int i = 0; i < _tex_count; i++)
                {
                    if (_textures[i].GetId() == tex.GetId())
                    {
                        tex_id = i;
                    }
                }
                if (tex_id < 0) /* if texture is not used yet */
                {
                    _textures[_tex_count] = tex;
                    tex_id = _tex_count;
                    _tex_count++;
                }
            }
            std::array<Vertex, 4> vertices = Quad::gen_vertices(pos, size, col, tex_id);
            std::array<unsigned int, 6> indices = Quad::gen_indices(_vertex_count);
            _vbo.AddData(vertices.data(), sizeof(vertices));
            _ibo.AddData(indices.data(), sizeof(indices));
            _index_count += 6;
            _vertex_count += 4;
        }

        /* Batch renderer optimization: 
         *      Create a VBO for each texture slot and keep filling it
         *      until it is full and needs to be flushed or a new texture
         *      is coming to be rendered and we need that slot
         */
        void Flush()
        {
            _vao.Bind();
            _shader.Bind();
            for (int i = 0; i < _tex_count; i++)
            {
                glBindTextureUnit(i, _textures[i].GetId());
                _shader.SetInt(std::string("u_textures2D[" + std::to_string(i) + "]").c_str(), i);
            }
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
            _tex_count = 0;
        }

        unsigned int GetNumOfBatches() const
        {
            return (_num_of_batches);
        }
    };

}