#include <print>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render/Window.hpp"
#include "render/Shader.hpp"
#include "render/utils.hpp"
#include "render/Buffers.hpp"

using namespace FT;

int main(void)
{
	Window win(500, 500, "QuadTrees");
	glClearColor(0.7, 0.25, 0.2, 1.0);

	ShaderSource src = read_shader(ASSETS_DIRECTORY"/basic.glsl");
	Shader sh(src.data[ShaderType::VERTEX], src.data[ShaderType::FRAGMENT]);
	
	float pos[3 * 3] = {
		-0.25,	-0.25,	0.0,
		 0.25,	-0.25,	0.0,
		 0.0,	 0.5,	0.0
	};
	float col[3 * 4] = {
		 1.0,	 0.0,	0.0,	1.0,
		 0.0,	 1.0,	0.0,	1.0,
		 0.0,	 0.0,	1.0,	1.0
	};
	float tex_coords[3 * 2] = {
		 1.0,	 0.0,
		 0.0,	 1.0,
		 0.0,	 0.0
	};
	float data[3 * 9] = {
		-0.25,	-0.25,	0.0,	1.0,	 0.0,	0.0,	1.0,	0.0,	0.0,
		 0.25,	-0.25,	0.0,	0.0,	 1.0,	0.0,	1.0,	0.0,	0.0,
		 0.0,	 0.5,	0.0,	0.0,	 0.0,	1.0,	1.0,	0.0,	0.0
	};

	/* VBO ONLY POS */
	VBO vbo_pos;
	vbo_pos.AddData(pos, sizeof(pos));
	/* VBO ONLY COLOR */
	VBO vbo_col;
	vbo_col.AddData(col, sizeof(col));
	/* VBO ONLY TEX_COORD */
	VBO vbo_tex_coords;
	vbo_tex_coords.AddData(tex_coords, sizeof(tex_coords));
	/* VBO POS AND COLOR */
	VBO vbo;
	vbo.AddData(data, sizeof(data));

	VAO vao;
	vao.AddVBO(vbo_pos, 0, 0, 3, GL_FLOAT, GL_FALSE, 0, sizeof(float) * 3);
	vao.AddVBO(vbo_col, 1, 1, 4, GL_FLOAT, GL_FALSE, 0, sizeof(float) * 4);
	vao.AddVBO(vbo_tex_coords, 2, 2, 2, GL_FLOAT, GL_FALSE, 0, sizeof(float) * 2);

	VAO vao2;
	vao2.AddVBO(vbo, 2);

	while (!win.ShouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		sh.Bind();
		vao.Bind();
		// vao2.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		win.PollEvents();
		win.SwapBuffers();
	}
	return (0);
}