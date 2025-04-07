#pragma once

#include <Window/Window_Controller.h>


namespace LR
{

    class Window_Input_Manager
    {
    private:
        bool m_active = true;

    public:
        Window_Input_Manager(bool _default_active = true) : m_active(_default_active) { }

    public:
        inline void set_active(bool _value) { m_active = _value; }
        inline bool active() const { return m_active; }

    public:
        inline bool key_prev_pressed(unsigned int _key) const { if(m_active) return LR::Window_Controller::instance().key_prev_pressed(_key); else return false; }
        inline bool mouse_button_prev_pressed(unsigned int _btn) const { if(m_active) return LR::Window_Controller::instance().mouse_button_prev_pressed(_btn); else return false; }

        inline bool is_mouse_button_down(unsigned int _btn) const { if(m_active) return LR::Window_Controller::instance().is_mouse_button_down(_btn); else return false; }
        inline bool is_mouse_button_up(unsigned int _btn) const { if(m_active) return LR::Window_Controller::instance().is_mouse_button_up(_btn); else return false; }
        inline bool mouse_button_was_pressed(unsigned int _btn) const { if(m_active) return LR::Window_Controller::instance().mouse_button_was_pressed(_btn); else return false; }
        inline bool mouse_button_was_released(unsigned int _btn) const { if(m_active) return LR::Window_Controller::instance().mouse_button_was_released(_btn); else return false; }

        inline bool is_key_down(unsigned int _key) const { if(m_active) return LR::Window_Controller::instance().is_key_down(_key); else return false; }
        inline bool is_key_up(unsigned int _key) const { if(m_active) return LR::Window_Controller::instance().is_key_up(_key); else return false; }
        inline bool key_was_pressed(unsigned int _key) const { if(m_active) return LR::Window_Controller::instance().key_was_pressed(_key); else return false; }
        inline bool key_was_released(unsigned int _key) const { if(m_active) return LR::Window_Controller::instance().key_was_released(_key); else return false; }

        inline int mouse_wheel_rotation() const { if(m_active) return LR::Window_Controller::instance().mouse_wheel_rotation(); else return 0; }

    };

}
