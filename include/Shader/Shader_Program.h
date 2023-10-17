#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <iostream>
#include <string>

#include <glew.h>
#include <mat4x4.hpp>

#include <Data_Structures/Map.h>
#include <Data_Structures/List.h>
#include <L_Debug/L_Debug.h>

#include <Shader/Shader_Types/Shader.h>
#include <Components/Texture.h>


namespace LR
{

    class Shader_Program
    {
    private:
        unsigned int m_program_handle = 0;
        LDS::List<Shader*> m_shader_objects;

    public:
        Shader_Program(const Shader_Program&) = delete;
        void operator=(const Shader_Program&) = delete;

    public:
        Shader_Program();
        Shader_Program(Shader_Program&& _other);
        void operator=(Shader_Program&& _other);

        ~Shader_Program();

//    private:
//        bool M_uniform_is_block(const std::string& _uniform_name) const;

    private:
        void M_debug() const;

    public:
        void reset();
        void add_shader(Shader* _shader);
        void init();

    };

}

#endif // SHADER_PROGRAM_H
