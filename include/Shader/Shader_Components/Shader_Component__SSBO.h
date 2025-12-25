#pragma once

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

}
