#include <Shader/Shader_Components/Shader_Texture_Component.h>

using namespace LR;


void Shader_Texture_Component::init(unsigned int _opengl_program_handle)
{
    Shader_Component::init(_opengl_program_handle);

    m_texture_uniform = M_extract_uniform_location(m_texture_uniform_name);
}



void Shader_Texture_Component::prepare_texture_uniform() const
{
    L_ASSERT(m_texture_uniform != -1);

    glUniform1i(m_texture_uniform, 0);
}



void Shader_Texture_Component::update(const Draw_Module* _draw_module)
{
    L_ASSERT(_draw_module);

    prepare_texture_uniform();
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Texture_Component_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Texture_Component_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_texture_uniform_name(texture_uniform_name);
}
