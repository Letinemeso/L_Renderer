#include <Uniform_Setters/Uniform_Setter.h>

#include <glew.h>

#include <Shader/Shader_Program.h>

using namespace LR;


void Uniform_Setter::init(const LR::Shader_Program* _shader)
{
    m_uniform_location = glGetUniformLocation(_shader->handle(), m_uniform_name.c_str());
    L_ASSERT(m_uniform_location != -1);
}





BUILDER_STUB_NULL_CONSTRUCTION_FUNC(Uniform_Setter_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Uniform_Setter_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_uniform_name(uniform_name);
}






void Uniform_Setter__Float::apply() const
{
    L_ASSERT(uniform_location() != -1);
    glUniform1f(uniform_location(), m_value);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Uniform_Setter_Stub__Float)

BUILDER_STUB_INITIALIZATION_FUNC(Uniform_Setter_Stub__Float)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_value(value);
}






void Uniform_Setter__Vec2::apply() const
{
    L_ASSERT(uniform_location() != -1);
    glUniform2f(uniform_location(), m_value[0], m_value[1]);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Uniform_Setter_Stub__Vec2)

BUILDER_STUB_INITIALIZATION_FUNC(Uniform_Setter_Stub__Vec2)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_value(value);
}






void Uniform_Setter__Vec3::apply() const
{
    L_ASSERT(uniform_location() != -1);
    glUniform3f(uniform_location(), m_value[0], m_value[1], m_value[2]);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Uniform_Setter_Stub__Vec3)

BUILDER_STUB_INITIALIZATION_FUNC(Uniform_Setter_Stub__Vec3)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_value(value);
}






