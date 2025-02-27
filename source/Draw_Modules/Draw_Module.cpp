#include <Draw_Modules/Draw_Module.h>

#include <Renderer/Renderer.h>
#include <Draw_Order_Controller/Draw_Order_Controller.h>
#include <Shader/Shader_Manager.h>

using namespace LR;


Draw_Module::Draw_Module()
{
    glGenVertexArrays(1, &m_vertex_array);
    bind_vertex_array();
}

Draw_Module::~Draw_Module()
{
    for(Graphics_Component_List::Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
        delete *it;

    glDeleteVertexArrays(1, &m_vertex_array);

    if(m_draw_order_controller && !m_should_update_draw_layer)
        m_draw_order_controller->unregister_module(this);
}



void Draw_Module::set_draw_layer(Draw_Order_Controller* _draw_order_controller, const std::string& _layer_name)
{
    if(_draw_order_controller == m_draw_order_controller && _layer_name == m_draw_layer)
        return;

    reset_draw_layer();

    m_draw_order_controller = _draw_order_controller;
    m_draw_layer = _layer_name;

    m_should_update_draw_layer = true;
}

void Draw_Module::reset_draw_layer()
{
    if(!m_draw_order_controller)
        return;

    m_draw_order_controller->unregister_module(this);
    m_draw_order_controller = nullptr;
    m_draw_layer.clear();

    set_draw_on_update(true);

    m_should_update_draw_layer = false;
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

void Draw_Module::bind_vertex_array() const
{
    glBindVertexArray(vertex_array());
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



void Draw_Module::M_update_draw_layer_if_needed()
{
    if(!m_should_update_draw_layer)
        return;

    m_draw_order_controller->register_module(m_draw_layer, this,
                                             [this]()
                                             {
                                                 draw();
                                             });
    set_draw_on_update(false);

    m_should_update_draw_layer = false;
}

void Draw_Module::M_update_internal(float _dt)
{
    bind_vertex_array();

    for(Graphics_Component_List::Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
        (*it)->update(_dt);

    if(m_should_recalculate_vertices_before_draw)
        recalculate_vertices_amount();
}



void Draw_Module::update(float _dt)
{
    M_update_draw_layer_if_needed();

    M_update_internal(_dt);

    if(m_draw_on_update)
        draw();
}

void Draw_Module::draw() const
{
    if(!transformation_data() || !transformation_data_prev_state())
        return;

    L_ASSERT(m_renderer);
    L_ASSERT(m_graphics_components.size() > 0);

    if(!m_visible)
        return;

    L_ASSERT(m_shader_program);

    m_renderer->set_shader_program(m_shader_program);
    m_renderer->prepare();

    transformation_data()->update_matrix();

    bind_vertex_array();

    for(Graphics_Component_List::Const_Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
        (*it)->prepare_to_draw();

    m_renderer->draw(this);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Draw_Module_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Draw_Module_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_visible(visible);

    M_apply_draw_mode(product);

    L_ASSERT(renderer);

    product->set_renderer(renderer);

    for(LV::Variable_Base::Childs_List::Const_Iterator it = graphics_component_stubs.begin(); !it.end_reached(); ++it)
    {
        Graphics_Component_Stub* stub = LV::cast_variable<Graphics_Component_Stub>(it->child_ptr);
        L_ASSERT(stub);
        product->add_graphics_component((Graphics_Component*)stub->construct());
    }

    if(draw_order_controller && draw_layer.size() > 0)
        product->set_draw_layer(draw_order_controller, draw_layer);

    L_ASSERT(shader_manager);
    Shader_Program* shader = shader_manager->get_shader_program(shader_id);
    product->set_shader_program(shader);
}



void Draw_Module_Stub::M_apply_draw_mode(Draw_Module* _product) const
{
    if(draw_mode.size() == 0)
        return;

    if(draw_mode == "GL_TRIANGLES")
        _product->set_draw_mode(GL_TRIANGLES);
    else if(draw_mode == "GL_LINES")
        _product->set_draw_mode(GL_LINES);
    else if(draw_mode == "GL_POINTS")
        _product->set_draw_mode(GL_POINTS);
    else
    {
        L_ASSERT(false);
    }
}



Draw_Module_Stub::~Draw_Module_Stub()
{
    for(LV::Variable_Base::Childs_List::Iterator it = graphics_component_stubs.begin(); !it.end_reached(); ++it)
        delete it->child_ptr;
}
