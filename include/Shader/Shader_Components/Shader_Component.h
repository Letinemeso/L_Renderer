#ifndef SHADER_COMPONENT_H
#define SHADER_COMPONENT_H

#include <Variable_Base.h>


namespace LR
{

    class Shader_Component
    {
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
        virtual void update() const = 0;

    };
}

#endif // SHADER_COMPONENT_H
