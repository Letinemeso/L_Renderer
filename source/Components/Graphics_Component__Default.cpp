#include <Components/Graphics_Component__Default.h>

using namespace LR;


Graphics_Component__Default::Graphics_Component__Default()
{

}

Graphics_Component__Default::~Graphics_Component__Default()
{
    delete m_reconstructor;
}



void Graphics_Component__Default::set_reconstructor(Graphics_Component_Reconstructor* _ptr)
{
    delete m_reconstructor;
    m_reconstructor = _ptr;

    if(m_reconstructor)
    {
        m_reconstructor->inject_graphics_component(this);
        if(m_parent_draw_module)
            m_reconstructor->inject_draw_module(m_parent_draw_module);
    }
}



void Graphics_Component__Default::M_on_parent_draw_module_set()
{
    if(m_reconstructor)
        m_reconstructor->inject_draw_module(m_parent_draw_module);
}



unsigned int Graphics_Component__Default::layout_index() const
{
    return buffer().layout_index();
}

unsigned int Graphics_Component__Default::vertices_amount() const
{
    if(buffer().layout_index() == 0xFFFFFFFF)
        return 0;

    L_ASSERT(buffer().floats_per_vertex() > 0);
    return buffer().size() / buffer().floats_per_vertex();
}

unsigned int Graphics_Component__Default::required_compute_shader_invocations() const
{
    return m_required_compute_shader_invocations;
}

void Graphics_Component__Default::setup_buffer() const
{
    buffer().setup_vertex_attrib_pointer();
}

void Graphics_Component__Default::update(float _dt)
{
    if(m_reconstructor)
        m_reconstructor->update(_dt);
}

void Graphics_Component__Default::prepare_to_draw() const
{
    m_buffer.bind_to_layout();

    Parent_Type::prepare_to_draw();
}

void Graphics_Component__Default::bind_for_computation() const
{
    m_buffer.bind_to_binding_point();
}





Graphics_Component_Stub__Default::~Graphics_Component_Stub__Default()
{
    delete reconstructor_stub;
}



BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Graphics_Component_Stub__Default)

BUILDER_STUB_INITIALIZATION_FUNC(Graphics_Component_Stub__Default)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    L_ASSERT(floats_per_vertex > 0);

    if(data.size() > 0)
    {
        product->buffer().resize(data.size());
        product->buffer().copy_array(data.raw_data(), data.size());
    }
    product->buffer().set_floats_per_vertex(floats_per_vertex);

    if(layout_index != 0xFFFFFFFF)
        product->buffer().set_layout_index(layout_index);
    if(binding_point_index != 0xFFFFFFFF)
        product->buffer().set_binding_point_index(binding_point_index);

    if(reconstructor_stub)
        product->set_reconstructor((Graphics_Component_Reconstructor*)reconstructor_stub->construct());

    product->set_required_compute_shader_invocations(required_compute_shader_invocations);
}
