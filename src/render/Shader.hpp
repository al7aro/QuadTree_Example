#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

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

        void SetMat4(const std::string& name, const glm::mat4& m) const
        {
            unsigned int loc = glGetUniformLocation(_id, name.c_str());
            glProgramUniformMatrix4fv(_id, loc, 1, GL_FALSE, glm::value_ptr(m));
        }
    };

}