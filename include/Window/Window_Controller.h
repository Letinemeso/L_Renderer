#pragma once

#include <vec2.hpp>

#include <L_Debug/L_Debug.h>
#include <Stuff/Message_Type.h>
#include <Stuff/Message_Translator.h>


struct GLFWwindow;

namespace LR
{

    MESSAGE_TYPE_DECLARATION_START(Message__Window_Resized)
    MESSAGE_TYPE_DECLARATION_END


    class Window_Controller final
    {
    private:
        GLFWwindow* m_window = nullptr;
        glm::vec2 m_window_size;

        bool m_keys_pressed_before[349] = { false };             //  magic numbers from glfw3.h
        bool m_mouse_buttons_pressed_before[8] = { false };

        glm::vec2 m_prev_cursor_pos;

        int m_mouse_wheel_rotation = 0;

        bool m_is_fullscreen = false;
        glm::vec2 m_saved_window_size;
        glm::vec2 m_saved_window_position;

    private:
        Window_Controller();

        Window_Controller(const Window_Controller&) = delete;
        Window_Controller(Window_Controller&&) = delete;
        void operator=(const Window_Controller&) = delete;
        void operator=(Window_Controller&&) = delete;

    public:
        ~Window_Controller();

    public:
        static inline Window_Controller& instance() { static Window_Controller s_instance; return s_instance; }

    public:
        void create_window(unsigned int _width, unsigned int _height, const char* _name);
        void terminate_window();

        void set_cursor_pos(double _x, double _y);
        void register_mouse_wheel_movement(int _value);
        void on_window_resized(int _new_width, int _new_height);
        void make_fullscreen(bool _fullscreen);

    public:
        void update();

        void swap_buffers();

    public:
        glm::vec2 get_cursor_position() const;
        glm::vec2 get_cursor_stride() const;

        const glm::vec2& get_window_size() const;
        float calculate_window_ratio() const;

        glm::vec2 get_window_position() const;

        bool key_prev_pressed(unsigned int _key) const;
        bool mouse_button_prev_pressed(unsigned int _btn) const;

        bool is_mouse_button_down(unsigned int _btn) const;
        bool is_mouse_button_up(unsigned int _btn) const;
        bool mouse_button_was_pressed(unsigned int _btn) const;
        bool mouse_button_was_released(unsigned int _btn) const;

        bool is_key_down(unsigned int _key) const;
        bool is_key_up(unsigned int _key) const;
        bool key_was_pressed(unsigned int _key) const;
        bool key_was_released(unsigned int _key) const;

        int mouse_wheel_rotation() const;

        void set_window_should_close(bool _value) const;
        bool window_should_close() const;

    };

}
