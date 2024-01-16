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



void Renderer::draw(const Draw_Module* _draw_module) const
{
    L_ASSERT(_draw_module);

    glBindVertexArray(_draw_module->vertex_array());

    m_shader_program->use();
    m_shader_program->update(_draw_module);

    glDrawArrays(GL_TRIANGLES /* TEMP */, 0, _draw_module->vertices_amount());
}
