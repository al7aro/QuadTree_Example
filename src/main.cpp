#include <print>
#include <chrono>
#include <cstdlib>
#include <ctime>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render/Window.hpp"
#include "render/Shader.hpp"
#include "render/Texture2D.hpp"
#include "utils.hpp"
#include "render/buffers/VAO.hpp"
#include "render/buffers/VBO.hpp"
#include "render/buffers/IBO.hpp"
#include "render/Renderer.hpp"
#include "render/Camera.hpp"

#include "QuadTree.hpp"

using namespace FT;

struct RenderData
{
	Window* win;
	Camera2D* cam;
	Renderer2D* renderer;
};

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	void* rdata_ptr = glfwGetWindowUserPointer(window);
	RenderData* rdata = static_cast<RenderData*>(rdata_ptr);
	rdata->cam->ScrollCallback(window, xoffset, yoffset);
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	static double xpos_prev = 0.0;
	static double ypos_prev = 0.0;
	void* rdata_ptr = glfwGetWindowUserPointer(window);
	RenderData* rdata = static_cast<RenderData*>(rdata_ptr);
	rdata->cam->CursorPosCallback(window, xpos, ypos, xpos_prev, ypos_prev);
	xpos_prev = xpos;
	ypos_prev = ypos;
	rdata->win->MouseMoveCallback(xpos, ypos);
}

static float rand_float(float min = 0.0, float max = 1.0)
{
	float r = float(std::rand()) / float(RAND_MAX);
	r = r * (max - min) + min;
	return (r);
}

int main(void)
{
	std::srand(std::time({}));
	/* WINDOW CREATION */
	Window win(500, 500, "QuadTrees");
	/* SET WINDOW CALLBACKS */
	win.SetCursorCallback(cursor_pos_callback);
	win.SetScrollCallback(scroll_callback);
	/* RENDERER SETUP */
	Renderer2D renderer;
	/* Camera2D SETUP */
	Camera2D camera(500, 500);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	RenderData rdata = { &win, &camera, &renderer };
	win.SetUserPointer(&rdata);

	/* SHADER & TEXTURE SETUP */
	ShaderSource src = read_shader(ASSETS_DIRECTORY"/basic.glsl");
	Shader sh(src.data[ShaderType::VERTEX], src.data[ShaderType::FRAGMENT]);
	TexData data = load_image(ASSETS_DIRECTORY"/grass.jpg");
	std::vector<Texture2D> tex_vec;
	/* Tex to have multiple textures (look similar tho) */
	for (int i = 0; i < 100; i++)
	{
		tex_vec.push_back(Texture2D(data));
	}

	/* FILL QUAD TREE AND RAW VECTOR */
	QuadTree<Quad> quad_tree(AABB{glm::vec2(0.0), 10.0}, 7);
	std::vector<Quad> raw_quads;
	glm::ivec2 quad_cnt(500.0);
	int k = 0;
	for (int i = 0; i <= quad_cnt.x; i++)
	{
		for (int j = 0; j <= quad_cnt.y; j++)
		{
			glm::vec2 pos(rand_float(-1.0, 1.0), rand_float(-1.0, 1.0));
			glm::vec2 size(rand_float(0.1, 1.5)/quad_cnt.x, rand_float(0.1, 1.5)/quad_cnt.y);
			glm::vec4 col(rand_float(), rand_float(), rand_float(), 1.0);
			if (rand_float(0.0, 1.0) < 0.75)
			{
				const Texture2D& tex = tex_vec[k % tex_vec.size()];
				quad_tree.Insert(pos, Quad{pos, glm::vec2(size.x), tex});
				raw_quads.push_back(Quad{pos, glm::vec2(size.x), tex});
			}
			else
			{
				quad_tree.Insert(pos, Quad{ pos, size, col });
				raw_quads.push_back(Quad{ pos, size, col });
			}
		}
	}

	/* START TIMER */
	std::chrono::steady_clock timer;
	double frame_time = 1.0;
	/* RENDERING LOOP */
	while (!win.ShouldClose())
	{
		auto start = timer.now();
		glClear(GL_COLOR_BUFFER_BIT);

		/* UPDATE CAMERA MOUSE MOVEMENT */
		camera.Update(win.GetWindowPtr(), frame_time/1000.0);
		/* UPLOAD CAMERA PROJECTION AND VIEW MATRICES TO GPU */
		sh.SetMat4("u_proj", camera.GetProjMatrix());
		sh.SetMat4("u_view", camera.GetViewMatrix());

		/* RENDER BEGINS */
		renderer.Begin(sh);
		/* USE QUERYRANGE TO RETURN A VECTOR OF MATCHING QUADS */
		//std::vector<Quad> in_view = quad_tree.QueryRange(win.GetMainCamera().bb);
		//int rendered_quads = in_view.size();
		/* DRAW ONLY QUADS IN VIEW */
		//for (auto& v : in_view)
		//{
		//	glm::vec4 col = v.col;
		//	if (win.MouseIntersects(v))
		//		col = glm::vec4(1.0f);
		//	renderer.DrawQuad(v.pos, v.size, col);
		//}
		/* USE QUERYMAP TO APPLY FUNCTION TO ALL MATCHING QUADS DIRECTLY */
		int rendered_quads = quad_tree.QueryMap(camera.bb,
			[&rdata](const Quad& q) {
				if (rdata.win->MouseIntersects(*rdata.cam, q))
					rdata.renderer->DrawQuad(q.pos, q.size, glm::vec4(1.0f));
				else
					rdata.renderer->DrawQuad(q);
			}
		);
		renderer.End();

		win.PollEvents();
		win.SwapBuffers();

		auto end = timer.now();
		frame_time = double(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
		win.SetTitleSuffix(" " + std::to_string(1000.0/frame_time) + "fps | "
							+ std::to_string(rendered_quads) + " quads | "
							+ std::to_string(renderer.GetNumOfBatches()) + " batches");
	}
	return (0);
}