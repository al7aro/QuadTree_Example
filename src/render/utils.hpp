#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

namespace FT {

    enum ShaderType
    {
        VERTEX = 0,
        FRAGMENT = 1,
        MAX = 2
    };

    struct ShaderSource
    {
        std::string data[ShaderType::MAX];
    };

    ShaderSource read_shader(const std::string& path)
    {
        ShaderSource src;
        std::fstream file(path);
        std::string line;
        ShaderType current_shader = ShaderType::MAX;

        if (!file.is_open())
        {
            std::cout << "ERROR: Could not open file [" << path << "]\n";
            return (src);
        }

        while (std::getline(file, line))
        {
            if (!line.find(".vertex"))
                current_shader = ShaderType::VERTEX;
            else if (!line.find(".fragment"))
                current_shader = ShaderType::FRAGMENT;
            else if (current_shader < ShaderType::MAX)
                src.data[current_shader].append(line + "\n");
        }
        return (src);
    }

}
