#include <Shader/Shader_Components/Shader_Component__SSBO.h>

#include <Stuff/String_With_Parameters.h>

using namespace LR;


BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Component_Stub__SSBO__Generic)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Component_Stub__SSBO__Generic)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    constexpr const char* Source =
        R"(

layout(std430, binding = {0}) buffer Buffer_{1}_{0}
{
    float {1}[];
};

)";

    LST::String_With_Parameters str(Source);
    str.replace_parameter(0, std::to_string(binding_index))
        .replace_parameter(1, data_name);

    product->set_source(str);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Component_Stub__SSBO__Float)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Component_Stub__SSBO__Float)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    std::string source =
R"(

layout(std430, binding = {0}) buffer Buffer_{1}_{0}
{
    float {1}[];
};

)";

    {
        LST::String_With_Parameters str(source);
        str.replace_parameter(0, std::to_string(binding_index))
            .replace_parameter(1, data_name);

        source = str;
    }

    if(generate_accessors > 0)
    {
        std::string amount_variable_name = data_name + "_elements_amount";

        source += "uint " + amount_variable_name + " = " + std::to_string(generate_accessors) + ";\n\n";

        for(unsigned int i = 0; i < generate_accessors; ++i)
            source += M_generate_accessor(amount_variable_name, i);
    }

    product->set_source(source);
}



std::string Shader_Component_Stub__SSBO__Float::M_generate_accessor(const std::string& _amount_variable_name, unsigned int _accessor_index) const
{
    constexpr const char* Accessor_Source =
R"(

float get_{0}_with_offset_{1}(uint _index)
{
    uint index_offset = {2} * _index + {1};
    if(index_offset >= {0}.length())
        return 0.0f;

    return {0}[index_offset];
}

void set_{0}_with_offset_{1}(uint _index, float _value)
{
    uint index_offset = {2} * _index + {1};
    if(index_offset >= {0}.length())
        return;

    {0}[index_offset] = _value;
}

)";

    LST::String_With_Parameters str(Accessor_Source);

    str.replace_parameter(0, data_name)
        .replace_parameter(1, std::to_string(_accessor_index))
        .replace_parameter(2, _amount_variable_name);

    return str;
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Component_Stub__SSBO__Vec3)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Component_Stub__SSBO__Vec3)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    std::string source =
R"(

layout(std430, binding = {0}) buffer Buffer_{1}_{0}
{
    float {1}[];
};

vec3 get_{1}(uint _index)
{
    vec3 result;

    uint index_offset = _index * 3;
    if(index_offset >= {1}.length() - 2)
        return result;

    for(uint i = 0; i < 3; ++i)
        result[i] = {1}[ index_offset + i ];

    return result;
}

void set_{1}(uint _index, vec3 _value)
{
    uint index_offset = _index * 3;
    if(index_offset >= {1}.length() - 2)
        return;

    for(uint i = 0; i < 3; ++i)
        {1}[index_offset + i] = _value[i];
}

)";

    LST::String_With_Parameters str(source);
    str.replace_parameter(0, std::to_string(binding_index))
        .replace_parameter(1, data_name);

    product->set_source(str);
}
