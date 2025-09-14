#include <print>
#include <chrono>
#include <cstdlib>
#include <ctime>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render/Window.hpp"
#include "render/Shader.hpp"
#include "render/utils.hpp"
#include "render/buffers/VAO.hpp"
#include "render/buffers/VBO.hpp"
#include "render/buffers/IBO.hpp"
#include "render/Renderer.hpp"
#include "render/Camera.hpp"

#include "QuadTree.hpp"

using namespace FT;

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	void* cam_ptr = glfwGetWindowUserPointer(window);
	Camera2D* cam = static_cast<Camera2D*>(cam_ptr);
	cam->ScrollCallback(window, xoffset, yoffset);
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	static double xpos_prev = 0.0;
	static double ypos_prev = 0.0;
	void* cam_ptr = glfwGetWindowUserPointer(window);
	Camera2D* cam = static_cast<Camera2D*>(cam_ptr);
	cam->CursorPosCallback(window, xpos, ypos, xpos_prev, ypos_prev);
	xpos_prev = xpos;
	ypos_prev = ypos;
}

float rand_float(float min = 0.0, float max = 1.0)
{
	float r = float(std::rand()) / float(RAND_MAX);
	r = r * (max - min) + min;
	return (r);
}

int main(void)
{
	std::srand(std::time({}));
	Window win(500, 500, "QuadTrees");
	glClearColor(0.0, 0.0, 0.0, 1.0);

	Renderer2D renderer;
	Camera2D camera;
	camera.window_height = 500;
	camera.window_width = 500;
	
	ShaderSource src = read_shader(ASSETS_DIRECTORY"/basic.glsl");
	Shader sh(src.data[ShaderType::VERTEX], src.data[ShaderType::FRAGMENT]);

	struct Shape
	{
		glm::vec2 pos;
		glm::vec2 size;
		glm::vec4 col;

		bool Contains(const glm::vec2& p)
		{
			glm::vec2 half_size = size / glm::vec2(2.0);
			if (half_size.x <= 0.0 || half_size.y <= 0.0)
                return (false);
            if (pos.x + half_size.x >= p.x &&
                pos.y + half_size.y >= p.y &&
                pos.x - half_size.x <= p.x &&
                pos.y - half_size.y <= p.y)
                return (true);
            return (false);
		}
	};
	QuadTree<Shape> quad_tree(camera.bb, 4);
	std::vector<Shape> raw_quads;
	glm::vec2 amount(100.0);
	for (int i = 0; i <= int(amount.x); i++)
	{
		for (int j = 0; j <= int(amount.y); j++)
		{
			glm::vec2 pos(rand_float(-1.0, 1.0), rand_float(-1.0, 1.0));
			glm::vec2 size(rand_float(0.1, 1.5)/amount.x, rand_float(0.1, 1.5)/amount.y);
			glm::vec4 col(rand_float(), rand_float(), rand_float(), 1.0);
			quad_tree.Insert(pos, Shape{pos, size, col});
			raw_quads.push_back(Shape{pos, size, col});
		}
	}

	glfwSetWindowUserPointer(win.GetWindowPtr(), &camera);
	glfwSetScrollCallback(win.GetWindowPtr(), scroll_callback);
	glfwSetCursorPosCallback(win.GetWindowPtr(), cursor_pos_callback);

	std::chrono::steady_clock timer;
	float frame_time = 1.0;
	while (!win.ShouldClose())
	{
		auto start = timer.now();
		glClear(GL_COLOR_BUFFER_BIT);

		sh.Bind();
		camera.Update(win.GetWindowPtr(), frame_time/1000.0);
		sh.SetMat4("u_proj", camera.GetProjMatrix());
		sh.SetMat4("u_view", camera.GetViewMatrix());
		renderer.Begin();
		std::vector<Shape> in_view = quad_tree.QueryRange(camera.bb);
		// std::vector<Shape> in_view = raw_quads;
		double xpos, ypos;
		glfwGetCursorPos(win.GetWindowPtr(), &xpos, &ypos);
		glm::vec2 view_mouse_pos = camera.WindowToView(glm::vec2(xpos, ypos));
		for (auto v : in_view)
		{
			glm::vec4 col = v.col;
			if (v.Contains(view_mouse_pos))
				col = glm::vec4(1.0);
			renderer.DrawQuad(v.pos, v.size, col);
		}
		renderer.End();

		win.PollEvents();
		win.SwapBuffers();

		auto end = timer.now();
		frame_time = double(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
		win.SetTitleSuffix(" " + std::to_string(1000.0f/frame_time) + "fps | "
							+ std::to_string(in_view.size()) + " quads | "
							+ std::to_string(renderer.GetNumOfBatches()) + " batches");
	}
	return (0);
}