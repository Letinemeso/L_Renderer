#include <Shader/Shader_Components/Shader_Transform_Component.h>

using namespace LR;


void Shader_Transform_Component::init(unsigned int _opengl_program_handle)
{
    Shader_Component::init(_opengl_program_handle);


}



void Shader_Transform_Component::update() const
{
    L_ASSERT(assigned_opengl_program_handle() != 0);


}
