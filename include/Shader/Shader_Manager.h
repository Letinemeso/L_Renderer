#pragma once

#include <Data_Structures/Map.h>

#include <Variable_Base.h>
#include <Builder_Stub.h>

#include <Shader/Shader_Program.h>


namespace LR
{

    class Shader_Manager : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Shader_Manager, LV::Variable_Base)

    private:
        using Shader_Program_Map = LDS::Map<std::string, Shader_Program*>;
        Shader_Program_Map m_shader_programs;

    public:
        Shader_Manager();
        ~Shader_Manager();

    public:
        void add_shader_program(const std::string& _id, Shader_Program* _program);  //  takes ownership

    public:
        Shader_Program* get_shader_program(const std::string& _id) const;

    };


    class Shader_Manager_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Manager_Stub, LV::Builder_Stub)

        INIT_CHILDS_LISTS
        ADD_CHILDS_LIST("Shader_Program__*", &shader_program_stubs)
        CHILDS_LISTS_END

    public:
        LV::Variable_Base::Childs_List shader_program_stubs;

    public:
        ~Shader_Manager_Stub();

    public:
        INIT_BUILDER_STUB(Shader_Manager)

    };

}
