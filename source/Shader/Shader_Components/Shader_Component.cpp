#include <Shader/Shader_Components/Shader_Component.h>

#include <glew.h>

using namespace LR;


Shader_Component::Shader_Component()
{

}

Shader_Component::~Shader_Component()
{

}



int Shader_Component::M_extract_uniform_location(const std::string& _name) const
{
    int result = glGetUniformLocation(assigned_opengl_program_handle(), _name.c_str());
    L_ASSERT(result != -1);

    return result;
}

Shader_Component::Vertex_Data Shader_Component::M_extract_input_buffer_location(const std::string& _name) const
{
    Vertex_Data result;

    int index = glGetAttribLocation(assigned_opengl_program_handle(), _name.c_str());
    L_ASSERT(index != -1);

    result.index = (unsigned int)index;

    int attribs_amount = 0;
    glGetProgramiv(assigned_opengl_program_handle(), GL_ACTIVE_ATTRIBUTES, &attribs_amount);

    const unsigned int variable_name_max_length = 256;
    char variable_name[variable_name_max_length] = { 0 };
    int actual_variable_name_length = 0;
    int variable_size = 0;
    unsigned int variable_type = 0;

    unsigned int attrib_i = 0;
    for(; attrib_i<(unsigned int)attribs_amount && _name != variable_name; ++attrib_i)
        glGetActiveAttrib(assigned_opengl_program_handle(), attrib_i, variable_name_max_length, &actual_variable_name_length, &variable_size, &variable_type, variable_name);

    L_ASSERT(_name == variable_name);

    result.floats_per_vertex = 4 - (GL_FLOAT_VEC4 - variable_type);    //  currently GL_FLOAT_VEC3 == GL_FLOAT_VEC2 + 1, GL_FLOAT_VEC4 == GL_FLOAT_VEC3 + 1. hopefully it stays that way

    return result;
}



void Shader_Component::init(unsigned int _opengl_program_handle)
{
    m_assigned_opengl_program_handle = _opengl_program_handle;
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Component_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Component_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_source(source);
    product->set_main_call(main_function_name);
}
