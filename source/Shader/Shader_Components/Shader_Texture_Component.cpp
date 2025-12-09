#include <Shader/Shader_Components/Shader_Texture_Component.h>

#include <glew.h>

#include <Stuff/String_With_Parameters.h>

using namespace LR;


void Shader_Texture_Component::init(unsigned int _opengl_program_handle)
{
    Shader_Component::init(_opengl_program_handle);

    m_texture_uniform = M_extract_uniform_location(m_texture_uniform_name);
}



void Shader_Texture_Component::prepare_texture_uniform() const
{
    L_ASSERT(m_texture_uniform != -1);

    glUniform1i(m_texture_uniform, 0);
}



void Shader_Texture_Component::update(const Draw_Module* _draw_module)
{
    L_ASSERT(_draw_module);

    prepare_texture_uniform();
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Texture_Component_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Texture_Component_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    constexpr const char* Source =
R"(

layout(location = {0}) out vec4 {1};

in vec2 {2};

uniform sampler2D {3};

void {4}()
{
    {1} = vec4(texture({3}, {2}));
}

)";

    LST::String_With_Parameters str(Source);
    str.replace_parameter(0, std::to_string(output_texture_id))
        .replace_parameter(1, output_varable_name)
        .replace_parameter(2, texture_coords_input_name)
        .replace_parameter(3, texture_uniform_name)
        .replace_parameter(4, main_function_name);

    product->set_source(str);
    product->set_main_call(main_function_name + "();");

    product->set_texture_uniform_name(texture_uniform_name);
}
