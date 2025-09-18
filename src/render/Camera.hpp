#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../AABB.hpp"

namespace FT {

    struct Camera2D
    {
        AABB bb = AABB{glm::vec2(0.0), 1.0};

        float aspect = 1.0;

        glm::vec2 pos_offset = glm::vec2(0.0);
        float mov_speed = 1.0;

        float rotation = 0.0;
        float rot_speed = 1.0;

        float zoom_speed = 1.5;
        float zoom_offset = 0.0;

        int window_width;
        int window_height;
            
        Camera2D(int p_width, int p_height)
            : window_width(p_width), window_height(p_height)
        {
		}

        glm::mat4 GetProjMatrix()
        {
            return (glm::ortho(-bb.half_size, bb.half_size, -bb.half_size, bb.half_size));
        }

        glm::mat4 GetViewMatrix()
        {
            glm::mat4 tr = glm::translate(glm::mat4(1.0), -glm::vec3(bb.pos, 0.0));
            glm::mat4 rot = glm::rotate(glm::mat4(1.0), rotation, glm::vec3(0.0, 0.0, 1.0));
            return (tr * rot);
        }

        void Update(GLFWwindow* window, float delta_time = 1.0)
        {
            if (glfwGetKey(window, GLFW_KEY_S))
                bb.pos.y -= mov_speed * delta_time;
            if (glfwGetKey(window, GLFW_KEY_W))
                bb.pos.y += mov_speed * delta_time;
            if (glfwGetKey(window, GLFW_KEY_A))
                bb.pos.x -= mov_speed * delta_time;
            if (glfwGetKey(window, GLFW_KEY_D))
                bb.pos.x += mov_speed * delta_time;
            if (glfwGetKey(window, GLFW_KEY_E))
                rotation += rot_speed * delta_time;
            if (glfwGetKey(window, GLFW_KEY_Q))
                rotation -= rot_speed * delta_time;
            if (zoom_offset)
            {
                bb.half_size = glm::clamp(bb.half_size + zoom_offset * zoom_speed * delta_time, 0.01f, 3.0f);
                zoom_offset = 0.0;
            }
        }

        void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
        {
            zoom_offset = -yoffset;
        }

        void CursorPosCallback(GLFWwindow* window, double xpos, double ypos, double xpos_prev, double ypos_prev)
        {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                float   x_pos_norm = (2.0 * bb.half_size) * xpos / 500 - bb.half_size;
                float   x_prev_norm = (2.0 * bb.half_size) * xpos_prev / 500 - bb.half_size;
                float   y_pos_norm = (2.0 * bb.half_size) * ypos / 500 - bb.half_size;
                float   y_prev_norm = (2.0 * bb.half_size) * ypos_prev / 500 - bb.half_size;
                bb.pos.x -= (x_pos_norm - x_prev_norm);
                bb.pos.y += (y_pos_norm - y_prev_norm);
            }
        }

        glm::vec2 WindowToView(const glm::vec2& p) const
        {
            glm::vec2 ret;
            ret.x = p.x / float(window_width);
            ret.y = p.y / float(window_height);
            ret.x = bb.pos.x + ret.x * bb.half_size * 2.0 - bb.half_size;
            ret.y = bb.pos.y -(ret.y * bb.half_size * 2.0 - bb.half_size);
            return (ret);
        }

    };

}