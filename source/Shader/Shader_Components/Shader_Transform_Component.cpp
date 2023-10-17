#include <Shader/Shader_Components/Shader_Transform_Component.h>

using namespace LR;


void Shader_Transform_Component::init(unsigned int _opengl_program_handle)
{
    Shader_Component::init(_opengl_program_handle);

    m_vertex_attribs.coordinates = M_extract_input_buffer_location("vs_in_pos");    //  TODO: probably should make this data not hardcoded
    m_vertex_attribs.colors = M_extract_input_buffer_location("vs_in_colors");
    m_vertex_attribs.texture_coordinates = M_extract_input_buffer_location("vs_in_tex_coords");

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

void Shader_Transform_Component::set_texture(const LR::Texture& _texture) const
{
    L_ASSERT(m_texture_uniform != -1);

    glUniform1i(m_texture_uniform, 0);

    _texture.bind();
}
