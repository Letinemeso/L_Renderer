#include "Shader/Shader.h"

using namespace LR;


Shader::Shader()
{

}

Shader::Shader(Shader&& _other)
{
    m_vertex_shader = _other.m_vertex_shader;
    _other.m_vertex_shader = 0;
    m_fragment_shader = _other.m_fragment_shader;
    _other.m_fragment_shader = 0;
    m_program = _other.m_program;
    _other.m_program = 0;

    m_projection_matrix_uniform = _other.m_projection_matrix_uniform;
    _other.m_projection_matrix_uniform = -1;
    m_transform_matrix_uniform = _other.m_transform_matrix_uniform;
    _other.m_transform_matrix_uniform = -1;
    m_texture_uniform = _other.m_texture_uniform;
    _other.m_texture_uniform = -1;
}

void Shader::operator=(Shader&& _other)
{
    m_vertex_shader = _other.m_vertex_shader;
    _other.m_vertex_shader = 0;
    m_fragment_shader = _other.m_fragment_shader;
    _other.m_fragment_shader = 0;
    m_program = _other.m_program;
    _other.m_program = 0;

    m_projection_matrix_uniform = _other.m_projection_matrix_uniform;
    _other.m_projection_matrix_uniform = -1;
    m_transform_matrix_uniform = _other.m_transform_matrix_uniform;
    _other.m_transform_matrix_uniform = -1;
    m_texture_uniform = _other.m_texture_uniform;
    _other.m_texture_uniform = -1;
}


Shader::~Shader()
{
    if(m_program > 0)
        glDeleteProgram(m_program);
    if(m_vertex_shader > 0)
        glDeleteShader(m_vertex_shader);
    if(m_fragment_shader > 0)
        glDeleteShader(m_fragment_shader);
}



void Shader::M_shader_debug(unsigned int _shader) const
{
	int result = 0;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &result);
	
	if (result == GL_FALSE)
	{
		int size = 0;
		char log[2048];
		glGetShaderInfoLog(_shader, 2048, &size, log);
        std::cout << log << "\n";
		
        L_ASSERT(false);
	}
}

void Shader::M_program_debug(unsigned int _program) const
{
	int result = 0;
	glGetProgramiv(_program, GL_LINK_STATUS, &result);

	if (result == GL_FALSE)
	{
		int size = 0;
		char log[2048];
		glGetProgramInfoLog(_program, 2048, &size, log);
        std::cout << log << "\n";
		
        L_ASSERT(false);
	}
}



void Shader::M_verify_vertex_attribs()
{
    LDS::Map<std::string, Vertex_Attribs::Vertex_Data*> supported_attributes;       //  TODO: should probably make this configurable
    supported_attributes.insert("vs_in_pos", &m_vertex_attribs.coordinates);
    supported_attributes.insert("vs_in_colors", &m_vertex_attribs.colors);
    supported_attributes.insert("vs_in_tex_coords", &m_vertex_attribs.texture_coordinates);

    int attribs_amount = 0;
    glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTES, &attribs_amount);

    const unsigned int variable_name_max_length = 256;
    char variable_name[variable_name_max_length] = { 0 };
    int actual_variable_name_length = 0;
    int variable_size = 0;
    unsigned int variable_type = 0;

    for(unsigned int i=0; i<(unsigned int)attribs_amount; ++i)
    {
        glGetActiveAttrib(m_program, i, variable_name_max_length, &actual_variable_name_length, &variable_size, &variable_type, variable_name);

        LDS::Map<std::string, Vertex_Attribs::Vertex_Data*>::Iterator maybe_attribute_it = supported_attributes.find(std::string(variable_name));
        L_ASSERT(maybe_attribute_it.is_ok());
        Vertex_Attribs::Vertex_Data* attribute_data = *maybe_attribute_it;

        attribute_data->floats_per_vertex = 4 - (GL_FLOAT_VEC4 - variable_type);    //  currently GL_FLOAT_VEC3 == GL_FLOAT_VEC2 + 1, GL_FLOAT_VEC4 = GL_FLOAT_VEC3 + 1. hopefully it stays that way
    }
}



void Shader::init(const std::string& _vertex_shader_source, const std::string& _fragment_shader_source)
{
    glDeleteShader(m_vertex_shader);
    glDeleteShader(m_fragment_shader);
    glDeleteProgram(m_program);

    m_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    m_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    m_program = glCreateProgram();

    const char* cstr_vsource = _vertex_shader_source.c_str();
    const char* cstr_fsource = _fragment_shader_source.c_str();

    glShaderSource(m_vertex_shader, 1, &cstr_vsource, 0);
    glCompileShader(m_vertex_shader);
    L_DEBUG_FUNC_1ARG(M_shader_debug, m_vertex_shader);

    glShaderSource(m_fragment_shader, 1, &cstr_fsource, 0);
    glCompileShader(m_fragment_shader);
    L_DEBUG_FUNC_1ARG(M_shader_debug, m_fragment_shader);


    glAttachShader(m_program, m_vertex_shader);
    glAttachShader(m_program, m_fragment_shader);

    glLinkProgram(m_program);
    L_DEBUG_FUNC_1ARG(M_program_debug, m_program);
    glUseProgram(m_program);

    M_verify_vertex_attribs();
}

void Shader::set_projection_matrix_uniform(const std::string& _name)
{
    m_projection_matrix_uniform = glGetUniformLocation(m_program, _name.c_str());
    L_ASSERT(m_projection_matrix_uniform != -1);
}

void Shader::set_transform_matrix_uniform(const std::string& _name)
{
    m_transform_matrix_uniform = glGetUniformLocation(m_program, _name.c_str());
    L_ASSERT(m_transform_matrix_uniform != -1);
}

void Shader::set_texture_uniform(const std::string& _name)
{
    m_texture_uniform = glGetUniformLocation(m_program, _name.c_str());
    L_ASSERT(m_texture_uniform != -1);
}


void Shader::set_projection_matrix(const glm::mat4x4& _matrix) const
{
    L_ASSERT(m_projection_matrix_uniform != -1);

    glUniformMatrix4fv(m_projection_matrix_uniform, 1, false, &_matrix[0][0]);
}

void Shader::set_transform_matrix(const glm::mat4x4& _matrix) const
{
    L_ASSERT(m_transform_matrix_uniform != -1);

    glUniformMatrix4fv(m_transform_matrix_uniform, 1, false, &_matrix[0][0]);
}

void Shader::set_texture(const LR::Texture& _texture) const
{
    L_ASSERT(m_texture_uniform != -1);
	
    glUniform1i(m_texture_uniform, 0);

    _texture.bind();
}
