#pragma once

#include <iostream>
#include <string>

#include <glew.h>
#include <mat4x4.hpp>

#include <Data_Structures/Map.h>
#include <Data_Structures/List.h>
#include <L_Debug/L_Debug.h>

#include <Shader/Shader_Types/Shader.h>
#include <Draw_Modules/Draw_Module_Base.h>


namespace LR
{

    class Shader_Program
    {
    private:
        unsigned int m_program_handle = 0;
        LDS::List<Shader*> m_shader_objects;

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

    private:
        void M_debug() const;

    public:
        void reset();
        void add_shader(Shader* _shader);
        void init();

    public:
        void update(const Draw_Module* _draw_module);

    public:
        void use() const;

    };

}
