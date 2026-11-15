#pragma once

#include <Data_Structures/Array.h>

#include <Shader/Shader_Components/Shader_Component.h>


namespace LR
{

    class Shader_Component_Stub__SSBO__Generic : public LR::Predefined_Shader_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Component_Stub__SSBO__Generic, LR::Predefined_Shader_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(unsigned int, binding_index)
        ADD_FIELD(std::string, data_name)
        FIELDS_END

    public:
        unsigned int binding_index = 0;
        std::string data_name;

    public:
        INIT_BUILDER_STUB(Shader_Component)

    };


    class Shader_Component_Stub__SSBO__Float : public LR::Predefined_Shader_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Component_Stub__SSBO__Float, LR::Predefined_Shader_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(unsigned int, binding_index)
        ADD_FIELD(std::string, data_name)
        ADD_FIELD(unsigned int, generate_accessors)
        FIELDS_END

    public:
        unsigned int binding_index = 0;
        std::string data_name;
        unsigned int generate_accessors = 1;

    public:
        INIT_BUILDER_STUB(Shader_Component)

    private:
        std::string M_generate_accessor(const std::string& _amount_variable_name, unsigned int _accessor_index) const;

    };


    class Shader_Component_Stub__SSBO__Vec3 : public LR::Predefined_Shader_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Component_Stub__SSBO__Vec3, LR::Predefined_Shader_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(unsigned int, binding_index)
        ADD_FIELD(std::string, data_name)
        FIELDS_END

    public:
        unsigned int binding_index = 0;
        std::string data_name;

    public:
        INIT_BUILDER_STUB(Shader_Component)

    };


    class Shader_Component_Stub__SSBO__Struct : public LR::Predefined_Shader_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Component_Stub__SSBO__Struct, LR::Predefined_Shader_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(unsigned int, binding_index)
        ADD_FIELD(std::string, buffer_name)
        ADD_FIELD(LDS::Vector<std::string>, data_names)
        ADD_FIELD(LDS::Vector<std::string>, data_types)
        FIELDS_END

    public:
        unsigned int binding_index = 0;
        std::string buffer_name;
        LDS::Vector<std::string> data_names;
        LDS::Vector<std::string> data_types;

    public:
        INIT_BUILDER_STUB(Shader_Component)

    public:
        Shader_Component_Stub__SSBO__Struct();
        ~Shader_Component_Stub__SSBO__Struct();

    private:
        enum Data_Types
        {
            Float,
            Vec3,
            Amount
        };
        inline static LDS::Array<unsigned int, Data_Types::Amount> m_data_types_sizes;

    private:
        Data_Types M_deduce_data_type(const std::string& _name) const;
        LDS::Vector<Data_Types> M_parse_types() const;
        unsigned int M_calculate_total_size(const LDS::Vector<Data_Types>& _types) const;

        std::string M_generate_accessor__float(const std::string& _data_name, unsigned int _local_offset, unsigned int _total_size) const;
        std::string M_generate_accessor__vec3(const std::string& _data_name, unsigned int _local_offset, unsigned int _total_size) const;
        std::string M_generate_accessor(const std::string& _data_name, unsigned int _local_offset, unsigned int _total_size, Data_Types _type) const;

    };

}
