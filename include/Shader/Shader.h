#pragma once

#include <Variable_Base.h>
#include <Builder_Stub.h>

#include <L_Debug/L_Debug.h>
#include <Data_Structures/List.h>

#include <Shader/Shader_Components/Shader_Component.h>
#include <Draw_Modules/Draw_Module.h>


namespace LR
{

    enum Shader_Type : unsigned int
    {
        Unknown = 0,
        Vertex = 1,
        Fragment = 2,
        Geometry = 3,
        Compute = 4
    };


    class Shader : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Shader, LV::Variable_Base)

    private:
        unsigned int m_assigned_opengl_program_handle = 0;
        unsigned int m_opengl_shader_handle = 0;

    public:
        using Shader_Components_List = LDS::List<Shader_Component*>;

    private:
        Shader_Type m_shader_type = Shader_Type::Unknown;
        std::string m_glsl_version;
        Shader_Components_List m_components;

    public:
        Shader(const Shader&) = delete;
        void operator=(const Shader&) = delete;

    public:
        Shader();
        Shader(Shader&& _other);
        void operator=(Shader&& _other);

        ~Shader();

    private:
        void M_debug(const char** _sources, unsigned int _sources_amount) const;
        bool M_component_already_added(Shader_Component* _component) const;
        unsigned int M_get_opengl_shader_type() const;

	public:
        inline void set_shader_type(Shader_Type _value) { m_shader_type = _value; }
        inline void set_glsl_version(const std::string& _value) { m_glsl_version = _value; }

        inline Shader_Type shader_type() const { return m_shader_type; }
        inline unsigned int handle() const { return m_opengl_shader_handle; }
        inline const Shader_Components_List& components() const { return m_components; }

    public:
        void reset();
        void add_component(Shader_Component* _component);
        void compile();
        void init(unsigned int _opengl_program_handle);

    public:
        template<typename Shader_Component_Type>
        Shader_Component_Type* get_shader_component_of_type();
        template<typename Shader_Component_Type>
        const Shader_Component_Type* get_shader_component_of_type() const;

    public:
        void update(const Draw_Module* _draw_module);

	};

    template<typename Shader_Component_Type>
    Shader_Component_Type* Shader::get_shader_component_of_type()
    {
        for(Shader_Components_List::Iterator it = m_components.begin(); !it.end_reached(); ++it)
        {
            Shader_Component_Type* component = LV::cast_variable<Shader_Component_Type>(*it);
            if(component)
                return component;
        }
        return nullptr;
    }

    template<typename Shader_Component_Type>
    const Shader_Component_Type* Shader::get_shader_component_of_type() const
    {
        for(Shader_Components_List::Const_Iterator it = m_components.begin(); !it.end_reached(); ++it)
        {
            const Shader_Component_Type* component = LV::cast_variable<Shader_Component_Type>(*it);
            if(component)
                return component;
        }
        return nullptr;
    }


    class Shader_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Stub, LV::Builder_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, shader_type)
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
        Shader_Type M_parse_shader_type() const;

    public:
        INIT_BUILDER_STUB(Shader)

    };

}
