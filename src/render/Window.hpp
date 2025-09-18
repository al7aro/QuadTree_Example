#pragma once

#include <string>
#include <print>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "debug.hpp"
#include "Quad.hpp"
#include "Camera.hpp"

namespace FT {

	class Window
	{
	private:
		GLFWwindow* _window;
		std::string _title;
		int _width, _height;
		double _mouse_x_pos, _mouse_y_pos;
	public:
		Window(int width, int height, const std::string& title)
			: _window(nullptr), _width(width), _height(height), _title(title),
			_mouse_x_pos(0.0), _mouse_y_pos(0.0)
		{
			/* Init GLFW */
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			_window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
			if (!_window) /* throw? */
			{
				std::println("ERROR: Window initializaion.");
			}
			glfwMakeContextCurrent(_window);
			/* Init GLAD */
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::println("ERROR: GLAD initialization.");
			}
			//glfwSwapInterval(0);
			/* DEBUG CALLBACK */
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(glDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}

		~Window()
		{
			glfwTerminate();
		}

		glm::vec2 GetMousePosWindow() const
		{
			return (glm::vec2(_mouse_x_pos, _mouse_y_pos));
		}

		void MouseMoveCallback(double xpos, double ypos)
		{
			_mouse_x_pos = xpos;
			_mouse_y_pos = ypos;
		}

		bool ShouldClose()
		{
			return (glfwWindowShouldClose(_window));
		}

		void PollEvents()
		{
			glfwPollEvents();
		}

		void SwapBuffers()
		{
			glfwSwapBuffers(_window);
		}

		void SetTitleSuffix(const std::string& suffix)
		{
			glfwSetWindowTitle(_window, std::string(_title + suffix).c_str());
		}

		GLFWwindow* GetWindowPtr() const
		{
			return (_window);
		}

		void SetCursorCallback(GLFWcursorposfun cb)
		{
			glfwSetCursorPosCallback(_window, cb);
		}

		void SetScrollCallback(GLFWscrollfun cb)
		{
			glfwSetScrollCallback(_window, cb);
		}

		void SetUserPointer(void* ptr)
		{
			glfwSetWindowUserPointer(_window, ptr);
		}

		void GetUserPointer(void** ptr)
		{
			*ptr = glfwGetWindowUserPointer(_window);
		}

		bool MouseIntersects(const Camera2D& cam, const Quad& quad) const
		{
			glm::vec2 view_mouse_pos = cam.WindowToView(glm::vec2(_mouse_x_pos, _mouse_y_pos));
			glm::vec4 col = quad.col;
			if (quad.Contains(view_mouse_pos))
				return (true);
			return (false);
		}
	};

}