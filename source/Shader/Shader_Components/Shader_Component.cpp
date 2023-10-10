#include <Shader/Shader_Components/Shader_Component.h>

using namespace LR;


Shader_Component::Shader_Component()
{

}

Shader_Component::~Shader_Component()
{

}



void Shader_Component::init(unsigned int _opengl_program_handle)
{
    m_assigned_opengl_program_handle = _opengl_program_handle;
}
