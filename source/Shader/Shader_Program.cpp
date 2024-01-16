#include <Shader/Shader_Program.h>

using namespace LR;


unsigned int Shader_Program::s_current_shader_program = 0;



Shader_Program::Shader_Program()
{

}

Shader_Program::Shader_Program(Shader_Program&& _other)
{
    m_shader_objects = (LDS::List<Shader*>&&)_other.m_shader_objects;
    m_program_handle = _other.m_program_handle;
    _other.m_program_handle = 0;
}

void Shader_Program::operator=(Shader_Program&& _other)
{
    m_shader_objects = (LDS::List<Shader*>&&)_other.m_shader_objects;
    m_program_handle = _other.m_program_handle;
    _other.m_program_handle = 0;
}


Shader_Program::~Shader_Program()
{
    reset();
}



void Shader_Program::M_debug() const
{
    int result = 0;
    glGetProgramiv(m_program_handle, GL_LINK_STATUS, &result);

    if (result == GL_TRUE)
        return;

    int size = 0;
    char log[2048];
    glGetProgramInfoLog(m_program_handle, 2048, &size, log);
    std::cout << log << "\n";

    L_ASSERT(false);
}



void Shader_Program::reset()
{
    for(LDS::List<Shader*>::Iterator it = m_shader_objects.begin(); !it.end_reached(); ++it)
    {
        Shader* shader = *it;
        delete shader;
    }
    m_shader_objects.clear();

    glDeleteProgram(m_program_handle);
    m_program_handle = 0;
}

void Shader_Program::add_shader(Shader *_shader)
{
    L_ASSERT(_shader);

    m_shader_objects.push_back(_shader);
}

void Shader_Program::init()
{
    L_ASSERT(m_program_handle == 0);

    m_program_handle = glCreateProgram();

    for(LDS::List<Shader*>::Iterator it = m_shader_objects.begin(); !it.end_reached(); ++it)
    {
        Shader* shader = *it;
        L_ASSERT(shader->handle() != 0);

        glAttachShader(m_program_handle, shader->handle());
    }

    glLinkProgram(m_program_handle);
    L_DEBUG_FUNC_NOARG(M_debug);
    glUseProgram(m_program_handle);
    s_current_shader_program = m_program_handle;

    for(LDS::List<Shader*>::Iterator it = m_shader_objects.begin(); !it.end_reached(); ++it)
    {
        Shader* shader = *it;

        shader->init(m_program_handle);
    }
}



void Shader_Program::update(const Draw_Module* _draw_module)
{
    L_ASSERT(_draw_module);

    for(LDS::List<Shader*>::Iterator it = m_shader_objects.begin(); !it.end_reached(); ++it)
        (*it)->update(_draw_module);
}



void Shader_Program::use() const
{
    if(s_current_shader_program == m_program_handle)
        return;

    glUseProgram(m_program_handle);

    s_current_shader_program = m_program_handle;
}


































































