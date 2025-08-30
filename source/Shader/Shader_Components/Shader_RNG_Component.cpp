#include <Shader/Shader_Components/Shader_RNG_Component.h>

#include <glew.h>

using namespace LR;


void Shader_RNG_Component::init(unsigned int _opengl_program_handle)
{
    Parent_Type::init(_opengl_program_handle);

    m_random_number_uniform = M_extract_uniform_location(m_random_number_uniform_name);
}



void Shader_RNG_Component::update(const LR::Draw_Module* _draw_module)
{
    Parent_Type::update(_draw_module);

    unsigned int random_number = rand();
    glUniform1ui(m_random_number_uniform, random_number);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_RNG_Component_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_RNG_Component_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_random_number_uniform_name(random_number_uniform_name);
}
