#include <Renderer/Renderer.h>

using namespace LR;


Renderer::Renderer()
{

}

Renderer::Renderer(const Renderer& _other)
{
    m_camera = _other.m_camera;
}

void Renderer::operator=(const Renderer& _other)
{
    m_camera = _other.m_camera;
}


Renderer::~Renderer()
{

}
