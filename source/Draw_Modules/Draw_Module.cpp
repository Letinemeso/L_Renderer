#include <Draw_Modules/Draw_Module.h>

#include <Renderer/Renderer.h>

using namespace LR;


Draw_Module::Draw_Module()
{
    glGenVertexArrays(1, &m_vertex_array);
    glBindVertexArray(m_vertex_array);
}

Draw_Module::~Draw_Module()
{
    for(Graphics_Component_List::Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
        delete *it;

    glDeleteVertexArrays(1, &m_vertex_array);
}



void Draw_Module::add_graphics_component(Graphics_Component *_ptr)
{
    L_DEBUG_FUNC_1ARG([this](Graphics_Component *_ptr)
    {
        for(auto it = m_graphics_components.begin(); !it.end_reached(); ++it)
        {
            L_ASSERT(*it != _ptr);
        }
    }, _ptr);

    if(m_graphics_components.size() == 0)
        m_vertices_amount = _ptr->buffer().size() / _ptr->buffer().floats_per_vertex();

    L_ASSERT( m_vertices_amount == _ptr->buffer().size() / _ptr->buffer().floats_per_vertex() );

    m_graphics_components.push_back(_ptr);

    if(_ptr->reconstructor())
        _ptr->reconstructor()->inject_draw_module(this);
}

void Draw_Module::recalculate_vertices_amount()
{
    L_ASSERT(m_graphics_components.size() > 0);

    Graphics_Component_List::Iterator it = m_graphics_components.begin();
    m_vertices_amount = (*it)->buffer().size() / (*it)->buffer().floats_per_vertex();

    L_DEBUG_FUNC_NOARG([this]()
    {
        for(Graphics_Component_List::Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
        {
            L_ASSERT((*it)->buffer().size() / (*it)->buffer().floats_per_vertex() == m_vertices_amount);
        }
    });
}



Graphics_Component* Draw_Module::get_graphics_component_with_buffer_index(unsigned int _index)
{
    for(Graphics_Component_List::Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
    {
        if((*it)->buffer().attrib_index() == _index)
            return *it;
    }
    return nullptr;
}

const Graphics_Component* Draw_Module::get_graphics_component_with_buffer_index(unsigned int _index) const
{
    for(Graphics_Component_List::Const_Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
    {
        if((*it)->buffer().attrib_index() == _index)
            return *it;
    }
    return nullptr;
}



void Draw_Module::update(float _dt)
{
    if(!m_visible)
        return;

    if(!m_draw_on_update)
        return;

    L_ASSERT(m_renderer);
    L_ASSERT(m_graphics_components.size() > 0);

    m_renderer->prepare();

    transformation_data()->update_matrix();

    glBindVertexArray(vertex_array());

    for(Graphics_Component_List::Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
        (*it)->update(_dt);

    if(m_should_recalculate_vertices_before_draw)
        recalculate_vertices_amount();

    m_renderer->draw(this);
}





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

    for(LV::Variable_Base::Childs_List::Const_Iterator it = graphics_component_stubs.begin(); !it.end_reached(); ++it)
    {
        Graphics_Component_Stub* stub = LV::cast_variable<Graphics_Component_Stub>(it->child_ptr);
        L_ASSERT(stub);
        product->add_graphics_component((Graphics_Component*)stub->construct());
    }
}



Draw_Module_Stub::~Draw_Module_Stub()
{
    for(LV::Variable_Base::Childs_List::Iterator it = graphics_component_stubs.begin(); !it.end_reached(); ++it)
        delete it->child_ptr;
}
