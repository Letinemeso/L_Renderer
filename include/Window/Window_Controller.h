#pragma once

#include <vec2.hpp>

#include <L_Debug/L_Debug.h>


struct GLFWwindow;

namespace LR
{

    class Window_Controller final
    {
    private:
        static GLFWwindow* m_window;
        static glm::vec2 m_window_size;

        static bool m_keys_pressed_before[349];             //  magic numbers from glfw3.h
        static bool m_mouse_buttons_pressed_before[8];

        static glm::vec2 m_prev_cursor_pos;

        static int m_mouse_wheel_rotation;

    private:
        Window_Controller() = delete;

    public:
        static void create_window(unsigned int _width, unsigned int _height, const char* _name);
        static void terminate_window();

        static void update();

    public:
        static bool window_should_close();
        static void swap_buffers();

        static void set_cursor_pos(double _x, double _y);

    public:
        static glm::vec2 get_cursor_position();
        static glm::vec2 get_cursor_stride();

        static const glm::vec2& get_window_size();
        static float calculate_window_ratio();

        static bool key_prev_pressed(unsigned int _key);
        static bool mouse_button_prev_pressed(unsigned int _btn);

        static bool is_mouse_button_down(unsigned int _btn);
        static bool is_mouse_button_up(unsigned int _btn);
        static bool mouse_button_was_pressed(unsigned int _btn);
        static bool mouse_button_was_released(unsigned int _btn);

        static bool is_key_down(unsigned int _key);
        static bool is_key_up(unsigned int _key);
        static bool key_was_pressed(unsigned int _key);
        static bool key_was_released(unsigned int _key);

        static int mouse_wheel_rotation();

    };

}
