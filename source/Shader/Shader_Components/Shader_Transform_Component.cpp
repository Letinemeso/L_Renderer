#include <Shader/Shader_Components/Shader_Transform_Component.h>

#include <Renderer/Renderer.h>

using namespace LR;


void Shader_Transform_Component::init(unsigned int _opengl_program_handle)
{
    Shader_Component::init(_opengl_program_handle);

    m_projection_matrix_uniform = M_extract_uniform_location(m_projection_matrix_uniform_name);
    m_transform_matrix_uniform = M_extract_uniform_location(m_transform_matrix_uniform_name);
}



void Shader_Transform_Component::set_projection_matrix(const glm::mat4x4 &_matrix) const
{
    glUniformMatrix4fv(m_projection_matrix_uniform, 1, false, &_matrix[0][0]);
}

void Shader_Transform_Component::set_transform_matrix(const glm::mat4x4 &_matrix) const
{
    glUniformMatrix4fv(m_transform_matrix_uniform, 1, false, &_matrix[0][0]);
}



void Shader_Transform_Component::update(const Draw_Module* _draw_module)
{
    L_ASSERT(_draw_module);

    set_projection_matrix(_draw_module->renderer()->camera()->matrix());
    set_transform_matrix(_draw_module->transformation_data()->matrix());
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Transform_Component_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Transform_Component_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_projection_matrix_uniform_name(projection_matrix_uniform_name);
    product->set_transform_matrix_uniform_name(transform_matrix_uniform_name);
}
