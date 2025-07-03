#pragma once

#include <vec2.hpp>
#include <vec3.hpp>

#include <Variable_Base.h>
#include <Builder_Stub.h>


namespace LR
{
    class Shader_Program;


    class Uniform_Setter : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter, LV::Variable_Base)

    private:
        std::string m_uniform_name;
        int m_uniform_location = -1;

    public:
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
        INIT_BUILDER_STUB(Uniform_Setter)

    };



    class Uniform_Setter__Float : public Uniform_Setter
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter__Float, LR::Uniform_Setter)

    private:
        float m_value = 0.0f;

    public:
        inline void set_value(float _value) { m_value = _value; }
        inline float value() const { return m_value; }

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
        INIT_BUILDER_STUB(Uniform_Setter__Float)

    };



    class Uniform_Setter__Vec2 : public Uniform_Setter
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter__Vec2, LR::Uniform_Setter)

    private:
        glm::vec2 m_value = { 0.0f, 0.0f };

    public:
        inline void set_value(const glm::vec2& _value) { m_value = _value; }
        inline const glm::vec2& value() const { return m_value; }

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
        INIT_BUILDER_STUB(Uniform_Setter__Vec2)

    };



    class Uniform_Setter__Vec3 : public Uniform_Setter
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter__Vec3, LR::Uniform_Setter)

    private:
        glm::vec3 m_value = { 0.0f, 0.0f, 0.0f };

    public:
        inline void set_value(const glm::vec3& _value) { m_value = _value; }
        inline const glm::vec3& value() const { return m_value; }

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
        INIT_BUILDER_STUB(Uniform_Setter__Vec3)

    };

}
