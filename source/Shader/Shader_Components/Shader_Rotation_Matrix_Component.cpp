#include <Shader/Shader_Components/Shader_Rotation_Matrix_Component.h>

#include <glew.h>

#include <Renderer/Renderer.h>

using namespace LR;


void Shader_Rotation_Matrix_Component::init(unsigned int _opengl_program_handle)
{
    Shader_Component::init(_opengl_program_handle);

    m_uniform = M_extract_uniform_location(m_uniform_name);
}



void Shader_Rotation_Matrix_Component::set_rotation_matrix(const glm::mat4x4 &_matrix) const
{
    glUniformMatrix4fv(m_uniform, 1, false, &_matrix[0][0]);
}



void Shader_Rotation_Matrix_Component::update(const Draw_Module* _draw_module)
{
    L_ASSERT(_draw_module);

    set_rotation_matrix(_draw_module->transformation_data()->rotation_matrix());
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Rotation_Matrix_Component_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Rotation_Matrix_Component_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_uniform_name(uniform_name);
}
