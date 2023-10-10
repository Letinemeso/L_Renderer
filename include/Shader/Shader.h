#ifndef __SHADER
#define __SHADER

#include <iostream>
#include <string>

#include <glew.h>
#include <mat4x4.hpp>

#include <Data_Structures/Map.h>
#include <L_Debug/L_Debug.h>

#include <Components/Texture.h>


namespace LR
{

	class Shader
    {
	private:
        unsigned int m_opengl_shader_handle = 0;

    private:
        std::string m_source;

    public:
        Shader(const Shader&) = delete;
        void operator=(const Shader&) = delete;

    public:
        Shader();
        Shader(Shader&& _other);
        void operator=(Shader&& _other);

        virtual ~Shader();

    private:
        void M_debug() const;

    private:
        virtual inline unsigned int shader_type() const = 0;

	public:
        void init(const std::string& _source);

    public:
        inline unsigned int handle() const { return m_opengl_shader_handle; }

	};

}

#endif
