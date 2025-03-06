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



void Renderer::prepare(const Draw_Module* _draw_module) const
{
    m_shader_program->use();
    m_shader_program->update(_draw_module);
    _draw_module->bind_vertex_array();
}
