#pragma once

#include <Variable_Base.h>
#include <Builder_Stub.h>

#include <glew.h>

#include <Draw_Modules/Draw_Module.h>


namespace LR
{

    class Shader_Component : public LV::Variable_Base
    {
    public:
        struct Vertex_Data
        {
            Vertex_Data() { }
            Vertex_Data(unsigned int _index, unsigned int _floats_per_vertex) : index(_index), floats_per_vertex(_floats_per_vertex) { }

            unsigned int index = 0;
            unsigned int floats_per_vertex = 0;
        };

    private:
        unsigned int m_assigned_opengl_program_handle = 0;

    private:
        std::string m_source;
        std::string m_main_call;

    public:
        Shader_Component();
        virtual ~Shader_Component();

    public:
        Shader_Component(const Shader_Component& _other) = delete;
        void operator=(const Shader_Component& _other) = delete;

    protected:
        inline unsigned int assigned_opengl_program_handle() const { return m_assigned_opengl_program_handle; }

    protected:
        int M_extract_uniform_location(const std::string& _name) const;
        Vertex_Data M_extract_input_buffer_location(const std::string& _name) const;

    public:
        inline void set_source(const std::string& _source) { m_source = _source; }
        inline void set_source(std::string&& _source) { m_source = (std::string&&)_source; }

        inline void set_main_call(const std::string& _main_call) { m_main_call = _main_call; }
        inline void set_main_call(std::string&& _main_call) { m_main_call = (std::string&&)_main_call; }

    public:
        inline const std::string& source() const { return m_source; }
        inline const std::string& main_call() const { return m_main_call; }

    public:
        virtual void init(unsigned int _opengl_program_handle);

    public:
        virtual void update(const Draw_Module* /*_draw_module*/) {  }

    };


    class Shader_Component_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Component_Stub, LV::Builder_Stub);

        INIT_FIELDS;
        ADD_FIELD(std::string, source)
        ADD_FIELD(std::string, main_function_name);
        FIELDS_END

    public:
        std::string source;
        std::string main_function_name;

    public:
        INIT_BUILDER_STUB(Shader_Component);

    };

}
