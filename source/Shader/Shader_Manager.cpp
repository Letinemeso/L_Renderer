#include <Shader/Shader_Manager.h>

using namespace LR;


Shader_Manager::Shader_Manager()
{

}

Shader_Manager::~Shader_Manager()
{
    for(Shader_Program_Map::Iterator it = m_shader_programs.iterator(); !it.end_reached(); ++it)
        delete *it;
}



void Shader_Manager::add_shader_program(const std::string& _id, Shader_Program* _program)
{
    L_ASSERT(!m_shader_programs.find(_id).is_ok());

    m_shader_programs.insert(_id, _program);
}



Shader_Program* Shader_Manager::get_shader_program(const std::string& _id) const
{
    Shader_Program_Map::Const_Iterator maybe_shader_it = m_shader_programs.find(_id);
    L_ASSERT(maybe_shader_it.is_ok());
    return *maybe_shader_it;
}





Shader_Manager_Stub::~Shader_Manager_Stub()
{
    clear_childs_list(shader_program_stubs);
}



BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Shader_Manager_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Shader_Manager_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    for(LV::Variable_Base::Childs_List::Const_Iterator it = shader_program_stubs.begin(); !it.end_reached(); ++it)
    {
        L_ASSERT(LV::cast_variable<Shader_Program_Stub>(it->child_ptr));

        Shader_Program_Stub* stub = (Shader_Program_Stub*)it->child_ptr;
        Shader_Program* shader = Shader_Program_Stub::construct_from(stub);
        product->add_shader_program(it->name, shader);
    }
}
