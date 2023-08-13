#include <Renderer/Renderer.h>

using namespace LR;


Renderer::Renderer()
{

}

Renderer::Renderer(const Renderer& _other)
{
    m_camera = _other.m_camera;
    m_shader = _other.m_shader;
}

void Renderer::operator=(const Renderer& _other)
{
    m_camera = _other.m_camera;
    m_shader = _other.m_shader;
}


Renderer::~Renderer()
{

}



void Renderer::setup_matrix(const glm::mat4x4& _transform_matrix)
{
    m_shader->set_projection_matrix(m_camera->matrix());
    m_shader->set_transform_matrix(_transform_matrix);
}

void Renderer::setup_texture(const LR::Texture& _texture)
{
    m_shader->set_texture(_texture);
}

void Renderer::bind_vertex_array(unsigned int _vertex_array)
{
    glBindVertexArray(_vertex_array);
}



void Renderer::draw(unsigned int _draw_mode, unsigned int _vertices_amount) const
{
    glDrawArrays(_draw_mode, 0, _vertices_amount);
}
