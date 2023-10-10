#include "Shader/Shader.h"

using namespace LR;


Shader::Shader()
{

}

Shader::Shader(Shader&& _other)
{
    m_opengl_shader_handle = _other.m_opengl_shader_handle;
    _other.m_opengl_shader_handle = 0;

    m_source = (std::string&&)_other.m_source;
}

void Shader::operator=(Shader&& _other)
{
    m_opengl_shader_handle = _other.m_opengl_shader_handle;
    _other.m_opengl_shader_handle = 0;

    m_source = (std::string&&)_other.m_source;
}


Shader::~Shader()
{
    glDeleteShader(m_opengl_shader_handle);
}



void Shader::M_debug() const
{
	int result = 0;
    glGetShaderiv(m_opengl_shader_handle, GL_COMPILE_STATUS, &result);
	
    if (result == GL_TRUE)
        return;

    int size = 0;
    char log[2048];
    glGetShaderInfoLog(m_opengl_shader_handle, 2048, &size, log);
    std::cout << log << "\n";

    L_ASSERT(false);
}



void Shader::init(const std::string& _vertex_shader_source)
{
    glDeleteShader(m_opengl_shader_handle);
    m_opengl_shader_handle = glCreateShader(shader_type());

    const char* cstr_source = _vertex_shader_source.c_str();

    glShaderSource(m_opengl_shader_handle, 1, &cstr_source, 0);
    glCompileShader(m_opengl_shader_handle);
    L_DEBUG_FUNC_NOARG(M_debug);
}

