.vertex
#version 460 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec4 a_col;
layout (location = 2) in vec2 a_tex_coords;
layout (location = 3) in float a_tex_id;

out vec4 v_col;
out vec2 v_tex_coords;
out float v_tex_id;

uniform mat4 u_model = mat4(1.0);
uniform mat4 u_proj = mat4(1.0);
uniform mat4 u_view = mat4(1.0);

void main()
{
    v_col = a_col;
    v_tex_coords = vec2(a_tex_coords.x, -a_tex_coords.y);
    v_tex_id = a_tex_id;
    gl_Position = u_proj * u_view * u_model * vec4(a_pos, 1.0);
}

.fragment
#version 460 core

in vec4 v_col;
in vec2 v_tex_coords;
in float v_tex_id;

out vec4 frag_color;

uniform sampler2D u_textures2D[8 + 1];

void main()
{
    if (int(v_tex_id) >= 0)
    {
        frag_color = texture(u_textures2D[int(v_tex_id)], v_tex_coords);
    }
    else
    {
        frag_color = v_col;
    }
}
