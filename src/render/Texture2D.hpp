#pragma once

#include <glad/glad.h>

#include "../utils.hpp"

namespace FT {

    class Texture2D
    {
    private:
        unsigned int _id;
        TexData _data;
    public:
        Texture2D(const TexData& data)
            : _data(data)
        {
        }
    };

}