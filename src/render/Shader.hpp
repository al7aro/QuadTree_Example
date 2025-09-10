#pragma once

#include <string>

#include <glad/glad.h>

namespace FT {

    class Shader
    {
    private:
        unsigned int _id;
    public:
        Shader()
        {
            _id = glCreateProgram();
        }

        Shader(const std::string& v_src, const std::string& f_src)
            : Shader()
        {
            AddShader(v_src, GL_VERTEX_SHADER);
            AddShader(f_src, GL_FRAGMENT_SHADER);
            glLinkProgram(_id);
        }

        void Bind()
        {
            glUseProgram(_id);
        }

        void AddShader(const std::string& sh_src, unsigned int type)
        {
            unsigned int sh = glCreateShader(type);
            const char* src = sh_src.c_str();
            glShaderSource(sh, 1, &src, 0);
            glCompileShader(sh);
            glAttachShader(_id, sh);
            glDeleteShader(sh);
        }
    };

}