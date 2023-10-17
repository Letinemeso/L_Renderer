#include <Shader/Shader_Program.h>

using namespace LR;


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
    glDeleteProgram(m_program_handle);
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



//bool Shader_Program::M_uniform_is_block(const std::string &_uniform_name) const
//{
//    for(unsigned int i=0; i<_uniform_name.size(); ++i)
//        if(_uniform_name[i] == '.')
//            return true;
//    return false;
//}



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

    for(LDS::List<Shader*>::Iterator it = m_shader_objects.begin(); !it.end_reached(); ++it)
    {
        Shader* shader = *it;

        shader->init(m_program_handle);
    }
}
