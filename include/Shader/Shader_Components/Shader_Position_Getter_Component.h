#pragma once

#include <Shader/Shader_Components/Shader_Component.h>


namespace LR
{

    class Shader_Position_Getter_Component : public LR::Shader_Component
    {
    public:
        INIT_VARIABLE(LR::Shader_Position_Getter_Component, LR::Shader_Component)

    protected:
        std::string m_module_position_uniform_name;
        int m_module_position_uniform = -1;

    public:
        inline void set_module_position_uniform_name(const std::string& _value) { m_module_position_uniform_name = _value; }

    public:
        void init(unsigned int _opengl_program_handle) override;

    public:
        void update(const LR::Draw_Module* _draw_module) override;

    };


    class Shader_Position_Getter_Component_Stub : public LR::Predefined_Shader_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Position_Getter_Component_Stub, LR::Predefined_Shader_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, module_position_uniform_name)
        FIELDS_END

    public:
        std::string module_position_uniform_name = "module_position";

    public:
        INIT_BUILDER_STUB(Shader_Position_Getter_Component)

    };

}
