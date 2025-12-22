#include <Shader/Shader_Components/Shader_Dt_Component.h>

#include <glew.h>

#include <Stuff/String_With_Parameters.h>

using namespace LR;


void Shader_Dt_Component::init(unsigned int _opengl_program_handle)
{
    LR::Shader_Component::init(_opengl_program_handle);

    m_dt_uniform = M_extract_uniform_location(m_dt_uniform_name);
}



void Shader_Dt_Component::update(const LR::Draw_Module* _draw_module)
{
    LR::Shader_Component::update(_draw_module);

    glUniform1f(m_dt_uniform, m_dt_getter());
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Dt_Componen_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Dt_Componen_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    constexpr const char* Source =
R"(

uniform float {1};

)";

    LST::String_With_Parameters str(Source);
    str.replace_parameter(1, dt_uniform_name);

    product->set_source((std::string)str + additional_source);

    product->set_dt_uniform_name(dt_uniform_name);
    L_ASSERT(dt_getter);
    product->set_dt_getter(dt_getter);

    product->set_main_call(main_function_name);
}
