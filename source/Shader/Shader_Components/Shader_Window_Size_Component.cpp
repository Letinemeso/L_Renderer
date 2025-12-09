#include <Shader/Shader_Components/Shader_Window_Size_Component.h>

#include <glew.h>

#include <Stuff/String_With_Parameters.h>

#include <Window/Window_Controller.h>

using namespace LR;


void Shader_Window_Size_Component::init(unsigned int _opengl_program_handle)
{
    Shader_Component::init(_opengl_program_handle);

    m_window_size_vec_uniform = M_extract_uniform_location(m_window_size_vec_uniform_name);
}



void Shader_Window_Size_Component::update(const Draw_Module* _draw_module)
{
    L_ASSERT(_draw_module);
    L_ASSERT(m_window_size_vec_uniform != -1);

    const glm::vec2& window_size = LR::Window_Controller::instance().get_window_size();
    glUniform2f(m_window_size_vec_uniform, window_size[0], window_size[1]);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Window_Size_Component_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Window_Size_Component_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    constexpr const char* Source =
R"(

uniform vec2 {1};

)";

    LST::String_With_Parameters str(Source);
    str.replace_parameter(1, window_size_vec_uniform_name);

    product->set_source(str);

    product->set_window_size_vec_uniform_name(window_size_vec_uniform_name);
}
