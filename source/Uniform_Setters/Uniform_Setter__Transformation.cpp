#include <Uniform_Setters/Uniform_Setter__Transformation.h>

#include <glew.h>

#include <Draw_Modules/Draw_Module.h>

using namespace LR;


void Uniform_Setter__Transformation::apply() const
{
    L_ASSERT(m_parent_draw_module);

    const glm::mat4x4& transformation = m_parent_draw_module->transformation_data()->matrix();

    L_ASSERT(uniform_location() != -1);
    glUniformMatrix4fv(uniform_location(), 1, false, &transformation[0][0]);
}