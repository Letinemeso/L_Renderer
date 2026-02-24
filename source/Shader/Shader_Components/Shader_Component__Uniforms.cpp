#include <Shader/Shader_Components/Shader_Component__Uniforms.h>

#include <glew.h>

using namespace LR;


void Shader_Component__Uniform::init(unsigned int _opengl_program_handle)
{
    Parent_Type::init(_opengl_program_handle);

    m_uniform = M_extract_uniform_location(m_uniform_name);
}



BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Component_Stub__Uniform)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Component_Stub__Uniform)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    std::string source = "\nuniform " + m_uniform_type_as_string + " " + uniform_name + ";\n";
    product->set_source(source);
}





void Shader_Component__Uniform__Float::update(const Draw_Module*)
{
    glUniform1f(uniform(), m_value);
}
