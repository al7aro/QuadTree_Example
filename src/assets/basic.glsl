.vertex
#version 460 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec4 a_col;

out vec4 v_col;

void main()
{
    v_col = a_col;
    gl_Position = vec4(a_pos, 1.0);
}

.fragment
#version 460 core

in vec4 v_col;

out vec4 frag_color;

void main()
{
    frag_color = v_col;
}
