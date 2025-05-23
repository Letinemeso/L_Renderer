#include <Shader/Shader_Program.h>

#include <glew.h>

using namespace LR;


unsigned int Shader_Program::s_current_shader_program = 0;



Shader_Program::Shader_Program()
{

}

Shader_Program::Shader_Program(Shader_Program&& _other)
{
    m_shaders = (LDS::List<Shader*>&&)_other.m_shaders;
    m_program_handle = _other.m_program_handle;
    _other.m_program_handle = 0;
}

void Shader_Program::operator=(Shader_Program&& _other)
{
    m_shaders = (LDS::List<Shader*>&&)_other.m_shaders;
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
    for(LDS::List<Shader*>::Iterator it = m_shaders.begin(); !it.end_reached(); ++it)
    {
        Shader* shader = *it;
        delete shader;
    }
    m_shaders.clear();

    glDeleteProgram(m_program_handle);
    m_program_handle = 0;
}

void Shader_Program::add_shader(Shader *_shader)
{
    L_ASSERT(_shader);

    m_shaders.push_back(_shader);
}

void Shader_Program::init()
{
    L_ASSERT(m_program_handle == 0);

    m_program_handle = glCreateProgram();

    for(LDS::List<Shader*>::Iterator it = m_shaders.begin(); !it.end_reached(); ++it)
    {
        Shader* shader = *it;
        L_ASSERT(shader->handle() != 0);

        glAttachShader(m_program_handle, shader->handle());
    }

    glLinkProgram(m_program_handle);
    L_DEBUG_FUNC_NOARG(M_debug);
    glUseProgram(m_program_handle);
    s_current_shader_program = m_program_handle;

    for(LDS::List<Shader*>::Iterator it = m_shaders.begin(); !it.end_reached(); ++it)
    {
        Shader* shader = *it;

        shader->init(m_program_handle);
    }
}



Shader* Shader_Program::get_shader_of_type(Shader_Type _type)
{
    for(Shaders_List::Iterator it = m_shaders.begin(); !it.end_reached(); ++it)
    {
        Shader* shader = *it;
        if(shader->shader_type() == _type)
            return shader;
    }
    return nullptr;
}

const Shader* Shader_Program::get_shader_of_type(Shader_Type _type) const
{
    for(Shaders_List::Const_Iterator it = m_shaders.begin(); !it.end_reached(); ++it)
    {
        const Shader* shader = *it;
        if(shader->shader_type() == _type)
            return shader;
    }
    return nullptr;
}



void Shader_Program::update(const Draw_Module* _draw_module)
{
    L_ASSERT(_draw_module);

    for(LDS::List<Shader*>::Iterator it = m_shaders.begin(); !it.end_reached(); ++it)
        (*it)->update(_draw_module);
}

void Shader_Program::use() const
{
    if(s_current_shader_program == m_program_handle)
        return;

    glUseProgram(m_program_handle);

    s_current_shader_program = m_program_handle;
}





Shader_Program_Stub::~Shader_Program_Stub()
{
    clear_childs_list(shaders);
}



BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Program_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Program_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    for(LV::Variable_Base::Childs_List::Const_Iterator it = shaders.begin(); !it.end_reached(); ++it)
    {
        Shader_Stub* stub = (Shader_Stub*)it->child_ptr;
        L_ASSERT(LV::cast_variable<Shader_Stub>(stub));

        Shader* shader = Shader_Stub::construct_from(stub);
        product->add_shader(shader);
    }

    product->init();
}
