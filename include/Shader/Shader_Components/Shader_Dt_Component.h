#pragma once

#include <Shader/Shader_Components/Shader_Component.h>


namespace LR
{

    class Shader_Dt_Component : public LR::Shader_Component
    {
    public:
        INIT_VARIABLE(LR::Shader_Dt_Component, LR::Shader_Component)

    private:
        std::string m_dt_uniform_name;
        int m_dt_uniform = -1;
        LST::Function<float()> m_dt_getter;

    public:
        inline void set_dt_uniform_name(const std::string& _value) { m_dt_uniform_name = _value; }
        inline void set_dt_getter(const LST::Function<float()>& _value) { m_dt_getter = _value; }

    public:
        void init(unsigned int _opengl_program_handle) override;

    public:
        void update(const LR::Draw_Module* _draw_module) override;

    };


    class Shader_Dt_Componen_Stub : public LR::Predefined_Shader_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Dt_Componen_Stub, LR::Predefined_Shader_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, dt_uniform_name)
        FIELDS_END

    public:
        LST::Function<float()> dt_getter;

    public:
        std::string dt_uniform_name = "dt";

    public:
        INIT_BUILDER_STUB(Shader_Dt_Component)

    };

}
