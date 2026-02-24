#pragma once

#include <Shader/Shader_Components/Shader_Component.h>


namespace LR
{

    class Shader_Component__Uniform : public Shader_Component
    {
    public:
        INIT_VARIABLE(LR::Shader_Component__Uniform, LR::Shader_Component)

    private:
        std::string m_uniform_name;
        int m_uniform = -1;

    public:
        inline void set_uniform_name(const std::string& _value) { m_uniform_name = _value; }

        inline const std::string& uniform_name() const { return m_uniform_name; }
        inline int uniform() const { return m_uniform; }

    public:
        void init(unsigned int _opengl_program_handle) override;

    };

    class Shader_Component_Stub__Uniform : public Predefined_Shader_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Component_Stub__Uniform, LR::Predefined_Shader_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, uniform_name)
        FIELDS_END

    public:
        std::string uniform_name;

    public:
        INIT_BUILDER_STUB(Shader_Component__Uniform)

        INIT_BUILDER_STUB_SETTERS
        ADD_BUILDER_STUB_SETTER(set_uniform_name, uniform_name)
        BUILDER_STUB_SETTERS_END

    private:
        std::string m_uniform_type_as_string;

    protected:
        Shader_Component_Stub__Uniform(const std::string& _uniform_type_as_string) { m_uniform_type_as_string = _uniform_type_as_string; }

    };


    class Shader_Component__Uniform__Float : public Shader_Component__Uniform
    {
    public:
        INIT_VARIABLE(LR::Shader_Component__Uniform__Float, LR::Shader_Component__Uniform)

    private:
        float m_value = 0.0f;

    public:
        inline void set_value(float _value) { m_value = _value; }

    public:
        void update(const Draw_Module*) override;

    };

    class Shader_Component_Stub__Uniform__Float : public Shader_Component_Stub__Uniform
    {
    public:
        INIT_VARIABLE(LR::Shader_Component_Stub__Uniform__Float, LR::Shader_Component_Stub__Uniform)

        INIT_FIELDS
        ADD_FIELD(float, default_value)
        FIELDS_END

    public:
        float default_value;

    public:
        INIT_DEFAULT_BUILDER_STUB(Shader_Component__Uniform__Float)

        INIT_BUILDER_STUB_SETTERS
        ADD_BUILDER_STUB_SETTER(set_value, default_value)
        BUILDER_STUB_SETTERS_END

    public:
        Shader_Component_Stub__Uniform__Float() : Shader_Component_Stub__Uniform("float") { }

    };

}
