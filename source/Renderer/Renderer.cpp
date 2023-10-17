#include <Renderer/Renderer.h>

using namespace LR;


Renderer::Renderer()
{

}

Renderer::Renderer(const Renderer& _other)
{
    m_camera = _other.m_camera;
    m_shader_program = _other.m_shader_program;
}

void Renderer::operator=(const Renderer& _other)
{
    m_camera = _other.m_camera;
    m_shader_program = _other.m_shader_program;
}


Renderer::~Renderer()
{

}



void Renderer::bind_vertex_array(unsigned int _vertex_array)
{
    glBindVertexArray(_vertex_array);
}



void Renderer::draw(unsigned int _draw_mode, unsigned int _vertices_amount) const
{
    glDrawArrays(_draw_mode, 0, _vertices_amount);
}
