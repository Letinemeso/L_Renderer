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





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Component_Stub__SSBO__Struct)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Component_Stub__SSBO__Struct)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    L_ASSERT(data_names.size() > 0);
    L_ASSERT(data_names.size() == data_types.size());

    LDS::Vector<Data_Types> types = M_parse_types();
    unsigned int total_size = M_calculate_total_size(types);

    std::string source =
        R"(

layout(std430, binding = {0}) buffer Buffer_{1}_{0}
{
    float {1}[];
};

uint {1}_amount()
{
    return {1}.length() / {2};
}

)";

    LST::String_With_Parameters str(source);
    str.replace_parameter(0, std::to_string(binding_index))
        .replace_parameter(1, buffer_name)
        .replace_parameter(2, std::to_string(total_size));

    source = str;

    unsigned int current_offset = 0;
    for(unsigned int i = 0; i < types.size(); ++i)
    {
        source += M_generate_accessor( data_names[i], current_offset, total_size, types[i] );

        current_offset += m_data_types_sizes[types[i]];
    }

    product->set_source(source);
}



Shader_Component_Stub__SSBO__Struct::Shader_Component_Stub__SSBO__Struct()
{
    static bool s_initialized = false;
    if(s_initialized)
        return;

    s_initialized = true;

    m_data_types_sizes.mark_full();
    m_data_types_sizes[Data_Types::Float] = 1;
    m_data_types_sizes[Data_Types::Vec3] = 3;
}

Shader_Component_Stub__SSBO__Struct::~Shader_Component_Stub__SSBO__Struct()
{

}



Shader_Component_Stub__SSBO__Struct::Data_Types Shader_Component_Stub__SSBO__Struct::M_deduce_data_type(const std::string& _name) const
{
    if(_name == "float")
        return Data_Types::Float;
    else if(_name == "vec3")
        return Data_Types::Vec3;

    return Data_Types::Amount;
}

LDS::Vector<Shader_Component_Stub__SSBO__Struct::Data_Types> Shader_Component_Stub__SSBO__Struct::M_parse_types() const
{
    LDS::Vector<Data_Types> result(data_types.size());
    result.mark_full();

    for(unsigned int i = 0; i < data_types.size(); ++i)
    {
        Data_Types type = M_deduce_data_type(data_types[i]);
        L_ASSERT(type != Data_Types::Amount);

        result[i] = type;
    }

    return result;
}

unsigned int Shader_Component_Stub__SSBO__Struct::M_calculate_total_size(const LDS::Vector<Data_Types>& _types) const
{
    unsigned int result = 0;
    for(unsigned int i = 0; i < _types.size(); ++i)
        result += m_data_types_sizes[ _types[i] ];
    return result;
}


std::string Shader_Component_Stub__SSBO__Struct::M_generate_accessor__float(const std::string& _data_name, unsigned int _local_offset, unsigned int _total_size) const
{
    std::string source =
        R"(

float get_{0}(uint _index)
{
    uint index_offset = _index * {2} + {3};
    if(index_offset >= {1}.length())
        return 0.0f;

    return {1}[ index_offset ];
}

void set_{0}(uint _index, vec3 _value)
{
    uint index_offset = _index * {2} + {3};
    if(index_offset >= {1}.length())
        return;

    {1}[ index_offset ] = _value[i];
}

)";

    LST::String_With_Parameters str(source);
    str.replace_parameter(0, _data_name)
        .replace_parameter(1, buffer_name)
        .replace_parameter(2, std::to_string(_total_size))
        .replace_parameter(3, std::to_string(_local_offset));

    return str;
}

std::string Shader_Component_Stub__SSBO__Struct::M_generate_accessor__vec3(const std::string& _data_name, unsigned int _local_offset, unsigned int _total_size) const
{
    std::string source =
        R"(

vec3 get_{0}(uint _index)
{
    vec3 result;

    uint index_offset = _index * {2} + {3};
    if(index_offset >= {1}.length() - 2)
        return result;

    for(uint i = 0; i < 3; ++i)
        result[i] = {1}[ index_offset + i ];

    return result;
}

void set_{0}(uint _index, vec3 _value)
{
    uint index_offset = _index * {2} + {3};
    if(index_offset >= {1}.length() - 2)
        return;

    for(uint i = 0; i < 3; ++i)
        {1}[index_offset + i] = _value[i];
}

)";

    LST::String_With_Parameters str(source);
    str.replace_parameter(0, _data_name)
        .replace_parameter(1, buffer_name)
        .replace_parameter(2, std::to_string(_total_size))
        .replace_parameter(3, std::to_string(_local_offset));

    return str;
}

std::string Shader_Component_Stub__SSBO__Struct::M_generate_accessor(const std::string& _data_name, unsigned int _local_offset, unsigned int _total_size, Data_Types _type) const
{
    if(_type == Data_Types::Float)
        return M_generate_accessor__float(_data_name, _local_offset, _total_size);
    else if(_type == Data_Types::Vec3)
        return M_generate_accessor__vec3(_data_name, _local_offset, _total_size);

    L_ASSERT_WITH_INFO(false, "Attempt to generate accessor for unknown type of " + _data_name + " (" + std::to_string(_type) + ")");
    return {};
}
