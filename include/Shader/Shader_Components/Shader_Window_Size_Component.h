#pragma once

#include <mat4x4.hpp>

#include <Shader/Shader_Components/Shader_Component.h>


namespace LR
{

    class Shader_Window_Size_Component : public Shader_Component
    {
    public:
        INIT_VARIABLE(LR::Shader_Window_Size_Component, LR::Shader_Component)

    private:
        std::string m_window_size_vec_uniform_name;
        int m_window_size_vec_uniform = -1;

    public:
        inline void set_window_size_vec_uniform_name(const std::string& _value) { m_window_size_vec_uniform_name = _value; }

    public:
        void init(unsigned int _opengl_program_handle) override;

    public:
        void update(const Draw_Module* _draw_module) override;

    };


    class Shader_Window_Size_Component_Stub : public Shader_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Window_Size_Component_Stub, LR::Shader_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, window_size_vec_uniform_name)
        FIELDS_END

    public:
        std::string window_size_vec_uniform_name;

    public:
        INIT_BUILDER_STUB(Shader_Window_Size_Component)

    };

}
