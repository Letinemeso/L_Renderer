#pragma once

#include <Data_Structures/Map.h>
#include <Data_Structures/List.h>
#include <L_Debug/L_Debug.h>

#include <Variable_Base.h>
#include <Builder_Stub.h>

#include <glew.h>
#include <mat4x4.hpp>

#include <Shader/Shader.h>
#include <Draw_Modules/Draw_Module.h>


namespace LR
{

    class Shader_Program : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Shader_Program, LV::Variable_Base)

    public:
        using Shaders_List = LDS::List<Shader*>;

    private:
        unsigned int m_program_handle = 0;
        Shaders_List m_shaders;

    private:
        static unsigned int s_current_shader_program;

    public:
        Shader_Program(const Shader_Program&) = delete;
        void operator=(const Shader_Program&) = delete;

    public:
        Shader_Program();
        Shader_Program(Shader_Program&& _other);
        void operator=(Shader_Program&& _other);

        ~Shader_Program();

    public:
        inline const Shaders_List& shaders() const { return m_shaders; }

    private:
        void M_debug() const;

    public:
        void reset();
        void add_shader(Shader* _shader);
        void init();

    public:
        Shader* get_shader_of_type(Shader_Type _type);
        const Shader* get_shader_of_type(Shader_Type _type) const;

    public:
        void update(const Draw_Module* _draw_module);
        void use() const;

    };


    class Shader_Program_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Program_Stub, LV::Builder_Stub)

        INIT_CHILDS_LISTS
        ADD_CHILDS_LIST("Shader__*", &shaders)
        CHILDS_LISTS_END

    public:
        LV::Variable_Base::Childs_List shaders;

    public:
        ~Shader_Program_Stub();

    public:
        INIT_BUILDER_STUB(Shader_Program);

    };

}
