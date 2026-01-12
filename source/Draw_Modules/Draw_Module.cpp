#include <Draw_Modules/Draw_Module.h>

#include <glew.h>

#include <Renderer/Renderer.h>
#include <Binds_Controller/Binds_Controller.h>
#include <Draw_Order_Controller/Draw_Order_Controller.h>
#include <Shader/Shader_Manager.h>
#include <Draw_Modules/Draw_Calls/Draw_Call__Default.h>

using namespace LR;


Draw_Module::Draw_Module()
    : m_draw_mode(GL_TRIANGLES)
{

}

Draw_Module::~Draw_Module()
{
    for(Graphics_Component_List::Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
        delete *it;
    for(Uniform_Setter_List::Iterator it = m_graphics_uniform_setters.begin(); !it.end_reached(); ++it)
        delete *it;
    for(Uniform_Setter_List::Iterator it = m_compute_uniform_setters.begin(); !it.end_reached(); ++it)
        delete *it;

    if(m_draw_order_controller && !m_should_update_draw_layer)
        m_draw_order_controller->unregister_module(this);

    delete m_draw_call;
}



void Draw_Module::set_rendering_shader_program(Shader_Program* _ptr)
{
    m_rendering_shader_program = _ptr;
    if(!m_rendering_shader_program)
        return;

    M_init_uniform_setters(m_graphics_uniform_setters, _ptr);

    M_on_rendering_shader_program_set();
}

void Draw_Module::set_compute_shader_program(Shader_Program* _ptr)
{
    m_compute_shader_program = _ptr;
    M_update_compute_shader_work_groups_sizes();

    if(!m_compute_shader_program)
        return;

    M_init_uniform_setters(m_compute_uniform_setters, _ptr);

    M_on_compute_shader_program_set();
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

    if(!m_should_update_draw_layer)
        m_draw_order_controller->unregister_module(this);

    L_ASSERT(!m_draw_order_controller->is_module_registred(this));

    m_draw_order_controller = nullptr;
    m_draw_layer.clear();

    set_draw_on_update(true);

    m_should_update_draw_layer = false;
}



void Draw_Module::add_graphics_component(Graphics_Component *_ptr)
{
    L_ASSERT(!m_graphics_components.find(_ptr).is_ok());

    _ptr->set_parent_draw_module(this);

    m_graphics_components.push_back(_ptr);
}

void Draw_Module::add_graphics_uniform_setter(Uniform_Setter* _ptr)
{
    L_ASSERT(!m_graphics_uniform_setters.find(_ptr).is_ok());

    m_graphics_uniform_setters.push_back(_ptr);

    if(m_rendering_shader_program)
        _ptr->init(m_rendering_shader_program);
}

void Draw_Module::add_compute_uniform_setter(Uniform_Setter* _ptr)
{
    L_ASSERT(!m_compute_uniform_setters.find(_ptr).is_ok());

    m_compute_uniform_setters.push_back(_ptr);

    if(m_compute_shader_program)
        _ptr->init(m_compute_shader_program);
}


void Draw_Module::apply_draw_rule() const
{
    L_ASSERT(m_rendering_shader_program->draw_rule());
    m_rendering_shader_program->draw_rule()->use();
}



Graphics_Component* Draw_Module::get_graphics_component_with_buffer_index(unsigned int _index)
{
    for(Graphics_Component_List::Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
    {
        if((*it)->layout_index() == _index)
            return *it;
    }
    return nullptr;
}

const Graphics_Component* Draw_Module::get_graphics_component_with_buffer_index(unsigned int _index) const
{
    for(Graphics_Component_List::Const_Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
    {
        if((*it)->layout_index() == _index)
            return *it;
    }
    return nullptr;
}


Uniform_Setter* Draw_Module::get_graphics_uniform_setter_with_name(const std::string& _name) const
{
    for(Uniform_Setter_List::Const_Iterator it = m_graphics_uniform_setters.begin(); !it.end_reached(); ++it)
    {
        Uniform_Setter* setter = *it;
        if(setter->uniform_name() == _name)
            return setter;
    }
    return nullptr;
}

Uniform_Setter* Draw_Module::get_compute_uniform_setter_with_name(const std::string& _name) const
{
    for(Uniform_Setter_List::Const_Iterator it = m_compute_uniform_setters.begin(); !it.end_reached(); ++it)
    {
        Uniform_Setter* setter = *it;
        if(setter->uniform_name() == _name)
            return setter;
    }
    return nullptr;
}


unsigned int Draw_Module::calculate_vertices_amount() const
{
    L_ASSERT(m_graphics_components.size() > 0);

    unsigned int vertices_amount = 0;
    for(Graphics_Component_List::Const_Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
    {
        vertices_amount = (*it)->vertices_amount();
        if(vertices_amount > 0)
            break;
    }

    L_DEBUG_FUNC_NOARG([&]()
                       {
                           for(Graphics_Component_List::Const_Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
                           {
                               unsigned int vertices_amount_check = (*it)->vertices_amount();
                               L_ASSERT(vertices_amount_check == 0 || vertices_amount_check == vertices_amount);
                           }
                       });

    return vertices_amount;
}



void Draw_Module::M_update_compute_shader_work_groups_sizes()
{
    if(!m_compute_shader_program)
    {
        m_compute_shader_work_group_sizes = Compute_Shader_Work_Groups_Sizes();
        return;
    }

    GLint* groups_sizes = (GLint*)&m_compute_shader_work_group_sizes;       //  oooh what a crutch! i love it! it MUST stay here FOREVER. DO NOT remove at all costs.
    glGetProgramiv(m_compute_shader_program->handle(), GL_COMPUTE_WORK_GROUP_SIZE, groups_sizes);
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

unsigned int Draw_Module::M_calculate_necessary_computer_shader_incovations() const
{
    L_ASSERT(m_graphics_components.size() > 0);

    unsigned int invocations = 0;
    for(Graphics_Component_List::Const_Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
    {
        invocations = (*it)->required_compute_shader_invocations();
        if(invocations > 0)
            break;
    }

    L_ASSERT(invocations > 0);
    L_DEBUG_FUNC_NOARG([&]()
    {
        for(Graphics_Component_List::Const_Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
        {
            unsigned int invocations_check = (*it)->required_compute_shader_invocations();
            L_ASSERT(invocations_check == 0 || invocations_check == invocations);
        }
    });

    return invocations;
}

unsigned int Draw_Module::M_calculate_necessary_work_groups(unsigned int _work_group_size) const
{
    return (M_calculate_necessary_computer_shader_incovations() + _work_group_size - 1) / _work_group_size;
}

void Draw_Module::M_dispatch_compute_shader(Shader_Program* _shader, const Uniform_Setter_List& _setters) const
{
    L_ASSERT(_shader);

    _shader->use();
    _shader->update(this);

    M_apply_uniform_setters(_setters);

    for(Graphics_Component_List::Const_Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
    {
        Graphics_Component* component = *it;
        component->bind_for_computation();
    }

    unsigned int vertices_groups = M_calculate_necessary_work_groups(m_compute_shader_work_group_sizes.x);
    glDispatchCompute(vertices_groups, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void Draw_Module::M_update_internal(float _dt)
{
    L_ASSERT(m_rendering_shader_program->draw_rule());
    m_rendering_shader_program->draw_rule()->use();

    for(Graphics_Component_List::Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
        (*it)->update(_dt);
}

void Draw_Module::M_draw_internal() const
{
    L_ASSERT(m_draw_call);
    m_draw_call->draw(this);
}

void Draw_Module::M_init_uniform_setters(const Uniform_Setter_List& _setters, const Shader_Program* _shader) const
{
    for(Uniform_Setter_List::Const_Iterator it = _setters.begin(); !it.end_reached(); ++it)
    {
        Uniform_Setter* setter = *it;
        setter->init(_shader);
    }
}

void Draw_Module::M_apply_uniform_setters(const Uniform_Setter_List& _setters) const
{
    for(Uniform_Setter_List::Const_Iterator it = _setters.begin(); !it.end_reached(); ++it)
    {
        Uniform_Setter* setter = *it;
        setter->apply();
    }
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

    if(m_compute_shader_program)
        M_dispatch_compute_shader(m_compute_shader_program, m_compute_uniform_setters);

    L_ASSERT(m_rendering_shader_program);
    m_rendering_shader_program->draw_rule()->use();

    for(Graphics_Component_List::Const_Iterator it = m_graphics_components.begin(); !it.end_reached(); ++it)
        (*it)->prepare_to_draw();

    m_rendering_shader_program->use();
    m_rendering_shader_program->update(this);

    M_apply_uniform_setters(m_graphics_uniform_setters);

    M_draw_internal();
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Draw_Module_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Draw_Module_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_visible(visible);
    product->set_draw_on_update(draw_on_update);

    M_apply_draw_mode(product);
    M_apply_draw_call(product);

    L_ASSERT(renderer);

    product->set_renderer(renderer);

    L_ASSERT(shader_manager);
    Shader_Program* rendering_shader = shader_manager->get_shader_program(rendering_shader_id);
    product->set_rendering_shader_program(rendering_shader);

    if(compute_shader_id.size() > 0)
    {
        Shader_Program* compute_shader = shader_manager->get_shader_program(compute_shader_id);
        product->set_compute_shader_program(compute_shader);
    }

    rendering_shader->use();

    for(LV::Variable_Base::Childs_List::Const_Iterator it = graphics_component_stubs.begin(); !it.end_reached(); ++it)
    {
        L_ASSERT(LV::cast_variable<Graphics_Component_Stub>(it->child_ptr));
        Graphics_Component_Stub* stub = (Graphics_Component_Stub*)(it->child_ptr);
        product->add_graphics_component(Graphics_Component_Stub::construct_from(stub));
    }

    for(LV::Variable_Base::Childs_List::Const_Iterator it = graphics_uniform_setter_stubs.begin(); !it.end_reached(); ++it)
    {
        L_ASSERT(LV::cast_variable<Uniform_Setter_Stub>(it->child_ptr));
        Uniform_Setter_Stub* stub = (Uniform_Setter_Stub*)(it->child_ptr);
        product->add_graphics_uniform_setter(Uniform_Setter_Stub::construct_from(stub));
    }

    for(LV::Variable_Base::Childs_List::Const_Iterator it = compute_uniform_setter_stubs.begin(); !it.end_reached(); ++it)
    {
        L_ASSERT(LV::cast_variable<Uniform_Setter_Stub>(it->child_ptr));
        Uniform_Setter_Stub* stub = (Uniform_Setter_Stub*)(it->child_ptr);
        product->add_compute_uniform_setter(Uniform_Setter_Stub::construct_from(stub));
    }

    if(draw_order_controller && draw_layer.size() > 0)
        product->set_draw_layer(draw_order_controller, draw_layer);
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

void Draw_Module_Stub::M_apply_draw_call(Draw_Module* _product) const
{
    if(draw_call)
    {
        _product->set_draw_call( Draw_Call_Stub::construct_from(draw_call) );
        return;
    }

    Draw_Call_Stub__Default default_draw_call_stub;
    _product->set_draw_call( Draw_Call_Stub__Default::construct_from(&default_draw_call_stub) );
}



Draw_Module_Stub::~Draw_Module_Stub()
{
    clear_childs_list(graphics_component_stubs);
    clear_childs_list(graphics_uniform_setter_stubs);
    clear_childs_list(compute_uniform_setter_stubs);
}
