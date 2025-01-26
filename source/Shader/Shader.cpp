#include <Shader/Shader.h>

using namespace LR;


Shader::Shader()
{

}

Shader::Shader(Shader&& _other)
{
    m_opengl_shader_handle = _other.m_opengl_shader_handle;
    _other.m_opengl_shader_handle = 0;

    m_assigned_opengl_program_handle = _other.m_assigned_opengl_program_handle;
    _other.m_assigned_opengl_program_handle = 0;

    m_components = (LDS::List<Shader_Component*>&&)_other.m_components;
}

void Shader::operator=(Shader&& _other)
{
    m_opengl_shader_handle = _other.m_opengl_shader_handle;
    _other.m_opengl_shader_handle = 0;

    m_assigned_opengl_program_handle = _other.m_assigned_opengl_program_handle;
    _other.m_assigned_opengl_program_handle = 0;

    m_components = (LDS::List<Shader_Component*>&&)_other.m_components;
}


Shader::~Shader()
{
    for(LDS::List<Shader_Component*>::Iterator it = m_components.begin(); !it.end_reached(); ++it)
    {
        Shader_Component* component = *it;
        delete component;
    }

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
    std::cout << log << std::endl;

    L_ASSERT(false);
}

bool Shader::M_component_already_added(Shader_Component *_component) const
{
    for(LDS::List<Shader_Component*>::Const_Iterator it = m_components.begin(); !it.end_reached(); ++it)
    {
        Shader_Component* component = *it;
        if(component == _component)
            return true;
    }
    return false;
}



void Shader::reset()
{
    for(LDS::List<Shader_Component*>::Iterator it = m_components.begin(); !it.end_reached(); ++it)
    {
        Shader_Component* component = *it;
        delete component;
    }

    glDeleteShader(m_opengl_shader_handle);

    m_opengl_shader_handle = 0;
    m_assigned_opengl_program_handle = 0;
}

void Shader::add_component(Shader_Component *_component)
{
    L_ASSERT(_component);
    L_ASSERT(!M_component_already_added(_component));

    m_components.push_back(_component);
}

void Shader::compile()
{
    glDeleteShader(m_opengl_shader_handle);

    L_ASSERT(m_glsl_version.size() > 0);

    m_opengl_shader_handle = glCreateShader(shader_type());

    const char** sources = new const char*[m_components.size() + 2];

    unsigned int sources_index = 0;

    std::string glsl_version_str = "#version " + m_glsl_version + "\n\n";

    sources[sources_index] = glsl_version_str.c_str();
    ++sources_index;

    for(LDS::List<Shader_Component*>::Iterator it = m_components.begin(); !it.end_reached(); ++it)
    {
        Shader_Component* component = *it;
        sources[sources_index] = component->source().c_str();
        ++sources_index;
    }

    std::string main_func_str;
    main_func_str += "void main()\n{\n";

    for(LDS::List<Shader_Component*>::Iterator it = m_components.begin(); !it.end_reached(); ++it)
    {
        Shader_Component* component = *it;
        main_func_str += component->main_call();
        main_func_str += "\n";
    }

    main_func_str += "}\n";

    sources[sources_index] = main_func_str.c_str();
    ++sources_index;

    glShaderSource(m_opengl_shader_handle, sources_index, sources, 0);
    glCompileShader(m_opengl_shader_handle);
    L_DEBUG_FUNC_NOARG(M_debug);

    delete[] sources;
}

void Shader::init(unsigned int _opengl_program_handle)
{
    m_assigned_opengl_program_handle = _opengl_program_handle;

    for(LDS::List<Shader_Component*>::Iterator it = m_components.begin(); !it.end_reached(); ++it)
    {
        Shader_Component* component = *it;
        component->init(m_assigned_opengl_program_handle);
    }
}



void Shader::update(const Draw_Module *_draw_module)
{
    L_ASSERT(_draw_module);

    for(LDS::List<Shader_Component*>::Iterator it = m_components.begin(); !it.end_reached(); ++it)
        (*it)->update(_draw_module);
}





Shader_Stub::~Shader_Stub()
{
    clear_childs_list(shader_components);
}



unsigned int Shader_Stub::M_parse_shader_type() const
{
    if(shader_type == "Vertex")
        return GL_VERTEX_SHADER;
    else if(shader_type == "Fragment")
        return GL_FRAGMENT_SHADER;
    else if(shader_type == "Geometry")
        return GL_GEOMETRY_SHADER;

    L_ASSERT(false);    //  unregistred shader type
    return 0;
}



BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Stub);

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_glsl_version(glsl_version);
    product->set_shader_type(M_parse_shader_type());

    for(LV::Variable_Base::Childs_List::Const_Iterator it = shader_components.begin(); !it.end_reached(); ++it)
    {
        Shader_Component_Stub* stub = (Shader_Component_Stub*)it->child_ptr;
        L_ASSERT(LV::cast_variable<Shader_Component_Stub>(stub));

        Shader_Component* component = Shader_Component_Stub::construct_from(stub);
        product->add_component(component);
    }
}
