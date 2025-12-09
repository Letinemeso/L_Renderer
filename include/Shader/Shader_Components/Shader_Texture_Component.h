#pragma once

#include <mat4x4.hpp>

#include <Components/Graphics_Component__Texture.h>
#include <Shader/Shader_Components/Shader_Component.h>


namespace LR
{

    class Shader_Texture_Component : public Shader_Component
    {
    public:
        INIT_VARIABLE(LR::Shader_Texture_Component, LR::Shader_Component)

    private:
        std::string m_texture_uniform_name;
        int m_texture_uniform = -1;

    public:
        inline void set_texture_uniform_name(const std::string& _value) { m_texture_uniform_name = _value; }

    public:
        void init(unsigned int _opengl_program_handle) override;

    public:
        void prepare_texture_uniform() const;

    public:
        void update(const Draw_Module* _draw_module) override;

    };


    class Shader_Texture_Component_Stub : public Predefined_Shader_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Texture_Component_Stub, LR::Predefined_Shader_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(unsigned int, output_texture_id)
        ADD_FIELD(std::string, output_varable_name)
        ADD_FIELD(std::string, texture_coords_input_name)
        ADD_FIELD(std::string, texture_uniform_name)
        ADD_FIELD(std::string, main_function_name)
        FIELDS_END

    public:
        unsigned int output_texture_id = 0;
        std::string output_varable_name = "result_color";
        std::string texture_coords_input_name = "fs_in_texture_coords";
        std::string texture_uniform_name = "fs_in_texture";
        std::string main_function_name = "process_texture_coords";

    public:
        INIT_BUILDER_STUB(Shader_Texture_Component)

    };

}
