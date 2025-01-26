#pragma once

#include <Variable_Base.h>
#include <Builder_Stub.h>

#include <glew.h>

#include <L_Debug/L_Debug.h>
#include <Data_Structures/List.h>

#include <Shader/Shader_Components/Shader_Component.h>
#include <Draw_Modules/Draw_Module.h>


namespace LR
{

    class Shader : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Shader, LV::Variable_Base)

    private:
        unsigned int m_assigned_opengl_program_handle = 0;

	private:
        unsigned int m_opengl_shader_handle = 0;

    private:
        unsigned int m_shader_type = 0;
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

	public:
        inline void set_shader_type(unsigned int _value) { m_shader_type = _value; }
        inline void set_glsl_version(const std::string& _value) { m_glsl_version = _value; }

        inline unsigned int shader_type() const { return m_shader_type; }
        inline unsigned int handle() const { return m_opengl_shader_handle; }

    public:
        void reset();
        void add_component(Shader_Component* _component);
        void compile();
        void init(unsigned int _opengl_program_handle);

    public:
        void update(const Draw_Module* _draw_module);

	};


    class Shader_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Stub, LV::Builder_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, glsl_version)
        FIELDS_END

        INIT_CHILDS_LISTS
        ADD_CHILDS_LIST("Shader_Component__*", &shader_components)
        CHILDS_LISTS_END

    public:
        std::string shader_type;
        std::string glsl_version;

        LV::Variable_Base::Childs_List shader_components;

    public:
        ~Shader_Stub();

    private:
        unsigned int M_parse_shader_type() const;

    public:
        INIT_BUILDER_STUB(Shader);

    };

}
