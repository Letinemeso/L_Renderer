#include <Shader/Shader_Components/Shader_Position_Getter_Component.h>

#include <glew.h>

#include <Stuff/String_With_Parameters.h>

using namespace LR;


void Shader_Position_Getter_Component::init(unsigned int _opengl_program_handle)
{
    Parent_Type::init(_opengl_program_handle);

    m_module_position_uniform = M_extract_uniform_location(m_module_position_uniform_name);
}



void Shader_Position_Getter_Component::update(const LR::Draw_Module* _draw_module)
{
    Parent_Type::update(_draw_module);

    const glm::vec3& position = _draw_module->transformation_data()->position();
    glUniform3f(m_module_position_uniform, position.x, position.y, position.z);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Position_Getter_Component_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Position_Getter_Component_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    constexpr const char* Source =
R"(

uniform vec3 {1};

)";

    LST::String_With_Parameters str(Source);
    str.replace_parameter(1, module_position_uniform_name);

    product->set_source(str);

    product->set_module_position_uniform_name(module_position_uniform_name);
}
