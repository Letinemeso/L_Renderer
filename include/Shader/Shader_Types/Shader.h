#pragma once

#include <iostream>
#include <string>

#include <glew.h>

#include <L_Debug/L_Debug.h>
#include <Data_Structures/List.h>

#include <Shader/Shader_Components/Shader_Component.h>
#include <Draw_Modules/Draw_Module.h>


namespace LR
{

	class Shader
    {
    private:
        unsigned int m_assigned_opengl_program_handle = 0;

	private:
        unsigned int m_opengl_shader_handle = 0;

    private:
        std::string m_glsl_version;
        LDS::List<Shader_Component*> m_components;

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
        bool M_component_already_added(Shader_Component* _component) const;

    private:
        virtual inline unsigned int shader_type() const = 0;

	public:
        inline void set_glsl_version(const std::string& _glsl_version) { m_glsl_version = _glsl_version; }

    public:
        void reset();
        void add_component(Shader_Component* _component);
        void compile();
        void init(unsigned int _opengl_program_handle);

    public:
        void update(const Draw_Module* _draw_module);

    public:
        inline unsigned int handle() const { return m_opengl_shader_handle; }

	};

}
