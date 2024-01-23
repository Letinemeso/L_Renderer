#include <Draw_Modules/Draw_Module_Base.h>

#include <Renderer/Renderer.h>

using namespace LR;


INIT_FIELDS(LR::Draw_Module, LEti::Module)
FIELDS_END


Draw_Module::Draw_Module()
{
    glGenVertexArrays(1, &m_vertex_array);
    glBindVertexArray(m_vertex_array);
}

Draw_Module::~Draw_Module()
{
    glDeleteVertexArrays(1, &m_vertex_array);
}



void Draw_Module::add_graphics_component(Graphics_Component *_ptr)
{
    L_DEBUG_FUNC_1ARG([this](Graphics_Component *_ptr)
    {
        for(auto it = m_graphics_components.begin(); !it.end_reached(); ++it)
        {
            if(*it == _ptr)
                return false;
        }
        return true;
    }, _ptr);

    if(m_graphics_components.size() == 0)
        m_vertices_amount = _ptr->buffer().size() / _ptr->buffer().floats_per_vertex();

    L_ASSERT( m_vertices_amount == _ptr->buffer().size() / _ptr->buffer().floats_per_vertex() );

    m_graphics_components.push_back(_ptr);

//    _ptr->buffer().set_vertex_array(vertex_array());
}



void Draw_Module::update(float /*_dt*/)
{
    L_ASSERT(m_renderer);

    m_renderer->prepare();

    transformation_data()->update_matrix();

    glBindVertexArray(vertex_array());

    for(Graphics_Component_List::Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
        (*it)->prepare();

    m_renderer->draw(this);
}





INIT_FIELDS(LR::Draw_Module_Stub, LEti::Module_Stub)
FIELDS_END


LV::Variable_Base* Draw_Module_Stub::M_construct_product() const
{
    return new Draw_Module;
}

void Draw_Module_Stub::M_init_constructed_product(LV::Variable_Base* _product) const
{
    LEti::Module_Stub::M_init_constructed_product(_product);

    Draw_Module* product = (Draw_Module*)_product;

    L_ASSERT(renderer);

    product->set_renderer(renderer);

    for(Graphics_Component_Stubs_Map::Const_Iterator it = graphics_component_stubs.iterator(); !it.end_reached(); ++it)
        product->add_graphics_component((Graphics_Component*)((*it)->construct()));
}



Draw_Module_Stub::~Draw_Module_Stub()
{
    for(Graphics_Component_Stubs_Map::Iterator it = graphics_component_stubs.iterator(); !it.end_reached(); ++it)
        delete *it;
}
