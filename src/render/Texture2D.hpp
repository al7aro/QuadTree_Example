#pragma once

#include <glad/glad.h>

#include "../utils.hpp"

namespace FT {

    class Texture2D
    {
    private:
        unsigned int _id;
        TexData _data;

        void init()
        {
            glCreateTextures(GL_TEXTURE_2D, 1, &_id);
            glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

            GLenum format = GL_RGBA; // Always the same because i force stbi desired format to rgba
            GLenum internal = GL_RGBA8;
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTextureStorage2D(_id, 1, internal, _data.w, _data.h);
            glTextureSubImage2D(_id, 0, 0, 0, _data.w, _data.h, format, GL_UNSIGNED_BYTE, _data.data);
        }
    public:
        Texture2D()
            : _id(0)
        {}
        Texture2D(const TexData& data)
            : _data(data)
        {
            init();
        }

        void SetData(const TexData& p_data)
        {
            _data = p_data;
            init();
        }

        unsigned int GetId() const
        {
            return (_id);
        }

        const TexData GetTexData() const
        {
            return (_data);
        }
    };

}