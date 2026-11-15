#include <Uniform_Setters/Uniform_Setter.h>

#include <glew.h>

#include <Shader/Shader_Program.h>

using namespace LR;


void Uniform_Setter::init(const LR::Shader_Program* _shader)
{
    m_uniform_location = glGetUniformLocation(_shader->handle(), m_uniform_name.c_str());
    L_ASSERT_WITH_INFO(m_uniform_location != -1, "Not found uniform with name " + m_uniform_name);
}





void Uniform_Setter__Float::apply() const
{
    L_ASSERT(uniform_location() != -1);
    glUniform1f(uniform_location(), m_value);
}





void Uniform_Setter__Int::apply() const
{
    L_ASSERT(uniform_location() != -1);
    glUniform1i(uniform_location(), m_value);
}





void Uniform_Setter__UInt::apply() const
{
    L_ASSERT(uniform_location() != -1);
    glUniform1ui(uniform_location(), m_value);
}





void Uniform_Setter__Vec2::apply() const
{
    L_ASSERT(uniform_location() != -1);
    glUniform2f(uniform_location(), m_value[0], m_value[1]);
}





void Uniform_Setter__Vec3::apply() const
{
    L_ASSERT(uniform_location() != -1);
    glUniform3f(uniform_location(), m_value[0], m_value[1], m_value[2]);
}





void Uniform_Setter__Mat4x4::set_value(const LDS::Vector<float>& _value)
{
    if(_value.size() == 0)
        return;

    L_ASSERT(_value.size() == 16);

    m_value = glm::mat4x4(
        _value[0], _value[1], _value[2], _value[3],
        _value[4], _value[5], _value[6], _value[7],
        _value[8], _value[9], _value[10], _value[11],
        _value[12], _value[13], _value[14], _value[15]
        );
}



void Uniform_Setter__Mat4x4::apply() const
{
    L_ASSERT(uniform_location() != -1);
    glUniformMatrix4fv(uniform_location(), 1, false, &m_value[0][0]);
}
