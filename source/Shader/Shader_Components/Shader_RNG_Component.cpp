#include <Shader/Shader_Components/Shader_RNG_Component.h>

#include <glew.h>

#include <Stuff/String_With_Parameters.h>

using namespace LR;


void Shader_RNG_Component::init(unsigned int _opengl_program_handle)
{
    Parent_Type::init(_opengl_program_handle);

    m_random_number_uniform = M_extract_uniform_location(m_random_number_uniform_name);
}



void Shader_RNG_Component::update(const LR::Draw_Module* _draw_module)
{
    Parent_Type::update(_draw_module);

    unsigned int random_number = rand();
    glUniform1ui(m_random_number_uniform, random_number);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_RNG_Component_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_RNG_Component_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    constexpr const char* Source =
R"(

uniform uint {1};

uint random_number()
{
    uvec2 state = uvec2({1}, current_particle_index());

    uvec2 constants = uvec2(636413622u, 1442695040u);
    uvec2 combined = state * constants + uvec2(884889u, 127641u);

    uint a = combined.x;
    uint b = combined.y;

    a = a * 747796405u + 2891336453u;
    b = (b ^ (b >> 15)) * 1u;

    a = (a ^ (a >> 13)) * 621654629u;
    b = b * 1597334677u + 1u;

    uint result = a ^ b;
    result = result * 747796405u + 2891336453u;
    result = (result ^ (result >> 16)) * 1u;

    return result;
}

uint next_random_number(uint _prev_random)
{
    uint state = _prev_random * 747796405u + 2891336453u;
    uint word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}

uint limit_random_number(uint _seed, uint _lower_limit, uint _upper_limit)
{
    if(_lower_limit >= _upper_limit)
        return _lower_limit;

    uint limit = _upper_limit - _lower_limit;
    return _seed % limit + _lower_limit;
}

float limit_random_number_float(uint _seed, float _lower_limit, float _upper_limit)
{
    if(_lower_limit >= _upper_limit)
        return _lower_limit;

    float difference = _upper_limit - _lower_limit;
    float ratio = float(limit_random_number(_seed, 0, 10000)) * 0.0001f;

    return _lower_limit + (difference *  ratio);
}

)";

    LST::String_With_Parameters str(Source);
    str.replace_parameter(1, random_number_uniform_name);

    product->set_source(str);

    product->set_random_number_uniform_name(random_number_uniform_name);
}
