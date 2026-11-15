#pragma once

#include <vec2.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>

#include <Variable_Base.h>
#include <Builder_Stub.h>


namespace LR
{
    class Shader_Program;
    class Draw_Module;


    class Uniform_Setter : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter, LV::Variable_Base)

    protected:
        const Draw_Module* m_parent_draw_module = nullptr;

    private:
        std::string m_uniform_name;
        int m_uniform_location = -1;

    public:
        inline void set_parent_draw_module(const Draw_Module* _ptr) { m_parent_draw_module = _ptr; }

        inline void set_uniform_name(const std::string& _value) { m_uniform_name = _value; }

        inline const std::string& uniform_name() const { return m_uniform_name; }
        inline int uniform_location() const { return m_uniform_location; }

    public:
        virtual void init(const LR::Shader_Program* _shader);

    public:
        virtual void apply() const = 0;

    };


    class Uniform_Setter_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter_Stub, LV::Builder_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, uniform_name)
        FIELDS_END

    public:
        std::string uniform_name;

    public:
        INIT_NULL_BUILDER_STUB(Uniform_Setter)

        INIT_BUILDER_STUB_SETTERS
        ADD_DEFAULT_BUILDER_STUB_SETTER(uniform_name)
        BUILDER_STUB_SETTERS_END

    };



    class Uniform_Setter__Float : public Uniform_Setter
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter__Float, LR::Uniform_Setter)

    private:
        PRIVATE_FIELD_G_S(float, value, 0.0f);

    public:
        void apply() const override;

    };


    class Uniform_Setter_Stub__Float : public Uniform_Setter_Stub
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter_Stub__Float, LR::Uniform_Setter_Stub)

        INIT_FIELDS
        ADD_FIELD(float, value)
        FIELDS_END

    public:
        float value = 0.0f;

    public:
        INIT_DEFAULT_BUILDER_STUB(Uniform_Setter__Float)

        INIT_BUILDER_STUB_SETTERS
        ADD_DEFAULT_BUILDER_STUB_SETTER(value)
        BUILDER_STUB_SETTERS_END

    };



    class Uniform_Setter__Int : public Uniform_Setter
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter__Int, LR::Uniform_Setter)

    private:
        PRIVATE_FIELD_G_S(int, value, 0);

    public:
        void apply() const override;

    };


    class Uniform_Setter_Stub__Int : public Uniform_Setter_Stub
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter_Stub__Int, LR::Uniform_Setter_Stub)

        INIT_FIELDS
        ADD_FIELD(int, value)
        FIELDS_END

    public:
        int value = 0;

    public:
        INIT_DEFAULT_BUILDER_STUB(Uniform_Setter__Int)

        INIT_BUILDER_STUB_SETTERS
        ADD_DEFAULT_BUILDER_STUB_SETTER(value)
        BUILDER_STUB_SETTERS_END

    };



    class Uniform_Setter__UInt : public Uniform_Setter
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter__UInt, LR::Uniform_Setter)

    private:
        PRIVATE_FIELD_G_S(unsigned int, value, 0);

    public:
        void apply() const override;

    };


    class Uniform_Setter_Stub__UInt : public Uniform_Setter_Stub
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter_Stub__UInt, LR::Uniform_Setter_Stub)

        INIT_FIELDS
        ADD_FIELD(unsigned int, value)
        FIELDS_END

    public:
        unsigned int value = 0;

    public:
        INIT_DEFAULT_BUILDER_STUB(Uniform_Setter__UInt)

        INIT_BUILDER_STUB_SETTERS
        ADD_DEFAULT_BUILDER_STUB_SETTER(value)
        BUILDER_STUB_SETTERS_END

    };



    class Uniform_Setter__Vec2 : public Uniform_Setter
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter__Vec2, LR::Uniform_Setter)

    private:
        PRIVATE_FIELD_GR_SR(glm::vec2, value, glm::vec2(0.0f));

    public:
        void apply() const override;

    };


    class Uniform_Setter_Stub__Vec2 : public Uniform_Setter_Stub
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter_Stub__Vec2, LR::Uniform_Setter_Stub)

        INIT_FIELDS
        ADD_FIELD(glm::vec2, value)
        FIELDS_END

    public:
        glm::vec2 value = { 0.0f, 0.0f };

    public:
        INIT_DEFAULT_BUILDER_STUB(Uniform_Setter__Vec2)

        INIT_BUILDER_STUB_SETTERS
        ADD_DEFAULT_BUILDER_STUB_SETTER(value)
        BUILDER_STUB_SETTERS_END

    };



    class Uniform_Setter__Vec3 : public Uniform_Setter
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter__Vec3, LR::Uniform_Setter)

    private:
        PRIVATE_FIELD_GR_SR(glm::vec3, value, glm::vec3(0.0f));

    public:
        void apply() const override;

    };


    class Uniform_Setter_Stub__Vec3 : public Uniform_Setter_Stub
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter_Stub__Vec3, LR::Uniform_Setter_Stub)

        INIT_FIELDS
        ADD_FIELD(glm::vec3, value)
        FIELDS_END

    public:
        glm::vec3 value = { 0.0f, 0.0f, 0.0f };

    public:
        INIT_DEFAULT_BUILDER_STUB(Uniform_Setter__Vec3)

        INIT_BUILDER_STUB_SETTERS
        ADD_DEFAULT_BUILDER_STUB_SETTER(value)
        BUILDER_STUB_SETTERS_END

    };



    class Uniform_Setter__Mat4x4 : public Uniform_Setter
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter__Mat4x4, LR::Uniform_Setter)

    private:
        PRIVATE_FIELD_GR_SR(glm::mat4x4, value, glm::mat4x4(0.0f));

    public:
        void set_value(const LDS::Vector<float>& _value);

    public:
        void apply() const override;

    };


    class Uniform_Setter_Stub__Mat4x4 : public Uniform_Setter_Stub
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter_Stub__Mat4x4, LR::Uniform_Setter_Stub)

        INIT_FIELDS
        ADD_FIELD(LDS::Vector<float>, value)
        FIELDS_END

    public:
        LDS::Vector<float> value;

    public:
        INIT_DEFAULT_BUILDER_STUB(Uniform_Setter__Mat4x4)

        INIT_BUILDER_STUB_SETTERS
        ADD_DEFAULT_BUILDER_STUB_SETTER(value)
        BUILDER_STUB_SETTERS_END

    };

}
