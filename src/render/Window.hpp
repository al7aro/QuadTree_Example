#pragma once

#include <string>
#include <print>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "debug.hpp"

namespace FT {



	class Window
	{
	private:
		GLFWwindow* _window;
		std::string _title;
		int _width, _height;
	public:
		Window(int width, int height, const std::string& title)
			: _window(nullptr), _width(width), _height(height), _title(title)
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
	};

}