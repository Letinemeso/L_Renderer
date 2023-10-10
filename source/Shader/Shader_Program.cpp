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

    m_projection_matrix_uniform = _other.m_projection_matrix_uniform;
    _other.m_projection_matrix_uniform = -1;
    m_transform_matrix_uniform = _other.m_transform_matrix_uniform;
    _other.m_transform_matrix_uniform = -1;
    m_texture_uniform = _other.m_texture_uniform;
    _other.m_texture_uniform = -1;
}

void Shader_Program::operator=(Shader_Program&& _other)
{
    m_shader_objects = (LDS::List<Shader*>&&)_other.m_shader_objects;
    m_program_handle = _other.m_program_handle;
    _other.m_program_handle = 0;

    m_projection_matrix_uniform = _other.m_projection_matrix_uniform;
    _other.m_projection_matrix_uniform = -1;
    m_transform_matrix_uniform = _other.m_transform_matrix_uniform;
    _other.m_transform_matrix_uniform = -1;
    m_texture_uniform = _other.m_texture_uniform;
    _other.m_texture_uniform = -1;
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



bool Shader_Program::M_uniform_is_block(const std::string &_uniform_name) const
{
    for(unsigned int i=0; i<_uniform_name.size(); ++i)
        if(_uniform_name[i] == '.')
            return true;
    return false;
}




void Shader_Program::M_verify_vertex_attribs()
{
    m_vertex_attribs = Vertex_Attribs();

    LDS::Map<std::string, Vertex_Attribs::Vertex_Data*> supported_attributes;       //  TODO: should probably make this configurable
    supported_attributes.insert("vs_in_pos", &m_vertex_attribs.coordinates);
    supported_attributes.insert("vs_in_colors", &m_vertex_attribs.colors);
    supported_attributes.insert("vs_in_tex_coords", &m_vertex_attribs.texture_coordinates);

    int attribs_amount = 0;
    glGetProgramiv(m_program_handle, GL_ACTIVE_ATTRIBUTES, &attribs_amount);

    const unsigned int variable_name_max_length = 256;
    char variable_name[variable_name_max_length] = { 0 };
    int actual_variable_name_length = 0;
    int variable_size = 0;
    unsigned int variable_type = 0;

    for(unsigned int i=0; i<(unsigned int)attribs_amount; ++i)
    {
        glGetActiveAttrib(m_program_handle, i, variable_name_max_length, &actual_variable_name_length, &variable_size, &variable_type, variable_name);

        LDS::Map<std::string, Vertex_Attribs::Vertex_Data*>::Iterator maybe_attribute_it = supported_attributes.find(std::string(variable_name));
        L_ASSERT(maybe_attribute_it.is_ok());
        Vertex_Attribs::Vertex_Data* attribute_data = *maybe_attribute_it;

        attribute_data->floats_per_vertex = 4 - (GL_FLOAT_VEC4 - variable_type);    //  currently GL_FLOAT_VEC3 == GL_FLOAT_VEC2 + 1, GL_FLOAT_VEC4 = GL_FLOAT_VEC3 + 1. hopefully it stays that way
    }
}

void Shader_Program::M_extract_uniforms_data()
{
    m_uniform_matrices.clear();

    m_projection_matrix_uniform = glGetUniformLocation(m_program_handle, m_projection_matrix_uniform_name.c_str());
    m_transform_matrix_uniform = glGetUniformLocation(m_program_handle, m_transform_matrix_uniform_name.c_str());
    m_texture_uniform = glGetUniformLocation(m_program_handle, m_texture_uniform_name.c_str());

    int uniforms_amount = 0;
    glGetProgramiv(m_program_handle, GL_ACTIVE_UNIFORMS, &uniforms_amount);

    const unsigned int variable_name_max_length = 256;
    char variable_name[variable_name_max_length] = { 0 };
    int actual_variable_name_length = 0;
    int variable_size = 0;
    unsigned int variable_type = 0;

    for(unsigned int i=0; i<(unsigned int)uniforms_amount; ++i)
    {
        glGetActiveUniform(m_program_handle, i, variable_name_max_length, &actual_variable_name_length, &variable_size, &variable_type, variable_name);

        if(variable_name == m_projection_matrix_uniform_name || variable_name == m_transform_matrix_uniform_name || variable_name == m_texture_uniform_name)
            continue;

        if(M_uniform_is_block(variable_name))
            continue;

        int uniform_location = glGetUniformLocation(m_program_handle, variable_name);
        L_ASSERT(uniform_location != -1);   //  just in case

        if(variable_type == GL_FLOAT_MAT4)
            m_uniform_matrices.insert(std::string(variable_name), uniform_location);
        else if(variable_type == GL_FLOAT_VEC4)
            m_uniform_vectors.insert(std::string(variable_name), uniform_location);
        else
        {
            L_ASSERT(false);    // unsupported uniform type
        }
    }
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

    for(LDS::List<Shader*>::Iterator it = m_shader_objects.begin(); !it.end_reached(); ++it)
    {
        Shader* shader = *it;

        shader->init(m_program_handle);
    }

    M_verify_vertex_attribs();
    M_extract_uniforms_data();
}



void Shader_Program::set_matrix_uniform(const glm::mat4x4& _matrix, int _uniform_location) const
{
    L_ASSERT(_uniform_location != -1);

    glUniformMatrix4fv(_uniform_location, 1, false, &_matrix[0][0]);
}


void Shader_Program::set_projection_matrix(const glm::mat4x4& _matrix) const
{
    set_matrix_uniform(_matrix, m_projection_matrix_uniform);
}

void Shader_Program::set_transform_matrix(const glm::mat4x4& _matrix) const
{
    set_matrix_uniform(_matrix, m_transform_matrix_uniform);
}

void Shader_Program::set_texture(const LR::Texture& _texture) const
{
    L_ASSERT(m_texture_uniform != -1);

    glUniform1i(m_texture_uniform, 0);

    _texture.bind();
}



int Shader_Program::get_matrix_uniform_location(const std::string& _name) const
{
    L_ASSERT(_name.size() > 0);

    LDS::Map<std::string, int>::Const_Iterator maybe_uniform_it = m_uniform_matrices.find(_name);
    L_ASSERT(maybe_uniform_it.is_ok());

    return *maybe_uniform_it;
}
