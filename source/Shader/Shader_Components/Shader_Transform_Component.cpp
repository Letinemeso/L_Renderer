#include <Shader/Shader_Components/Shader_Transform_Component.h>

#include <Renderer/Renderer.h>

using namespace LR;


void Shader_Transform_Component::init(unsigned int _opengl_program_handle)
{
    Shader_Component::init(_opengl_program_handle);

    m_vertex_attribs.coordinates = M_extract_input_buffer_location(m_coords_input_buffer_name);
    m_vertex_attribs.colors = M_extract_input_buffer_location(m_colors_input_buffer_name);
    m_vertex_attribs.texture_coordinates = M_extract_input_buffer_location(m_texture_coords_input_buffer_name);

    m_projection_matrix_uniform = M_extract_uniform_location(m_projection_matrix_uniform_name);
    m_transform_matrix_uniform = M_extract_uniform_location(m_transform_matrix_uniform_name);
    m_texture_uniform = M_extract_uniform_location(m_texture_uniform_name);
}



void Shader_Transform_Component::set_projection_matrix(const glm::mat4x4 &_matrix) const
{
    glUniformMatrix4fv(m_projection_matrix_uniform, 1, false, &_matrix[0][0]);
}

void Shader_Transform_Component::set_transform_matrix(const glm::mat4x4 &_matrix) const
{
    glUniformMatrix4fv(m_transform_matrix_uniform, 1, false, &_matrix[0][0]);
}


void Shader_Transform_Component::prepare_texture_uniform() const
{
    L_ASSERT(m_texture_uniform != -1);

    glUniform1i(m_texture_uniform, 0);
}



void Shader_Transform_Component::update(const Draw_Module* _draw_module)
{
    L_ASSERT(_draw_module);

    set_projection_matrix(_draw_module->renderer()->camera()->matrix());
    set_transform_matrix(_draw_module->transformation_data()->matrix());

    prepare_texture_uniform();
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Transform_Component_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Transform_Component_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_projection_matrix_uniform_name(projection_matrix_uniform_name);
    product->set_transform_matrix_uniform_name(transform_matrix_uniform_name);
    product->set_texture_uniform_name(texture_uniform_name);
    product->set_coords_input_buffer_name(coords_input_buffer_name);
    product->set_colors_input_buffer_name(colors_input_buffer_name);
    product->set_texture_coords_input_buffer_name(texture_coords_input_buffer_name);
}
