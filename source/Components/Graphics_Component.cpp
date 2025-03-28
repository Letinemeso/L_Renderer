#include <Components/Graphics_Component.h>

using namespace LR;


Graphics_Component::Graphics_Component()
{

}

Graphics_Component::~Graphics_Component()
{
    delete m_reconstructor;
}



void Graphics_Component::set_reconstructor(Graphics_Component_Reconstructor* _ptr)
{
    delete m_reconstructor;
    m_reconstructor = _ptr;

    if(m_reconstructor)
        m_reconstructor->inject_graphics_component(this);
}



void Graphics_Component::update(float _dt)
{
    if(m_reconstructor)
        m_reconstructor->update(_dt);
}

void Graphics_Component::prepare_to_draw() const
{
    m_buffer.bind_to_layout();
    m_buffer.bind_to_binding_point();

    if(m_on_prepare_func)
        m_on_prepare_func(this);
}


void Graphics_Component::bind_for_computation() const
{
    m_buffer.bind_to_binding_point();
}





Graphics_Component_Stub::~Graphics_Component_Stub()
{
    delete reconstructor_stub;
}



BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Graphics_Component_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Graphics_Component_Stub)
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

    if(on_prepare_func)
        product->set_on_prepare_func(on_prepare_func);

    if(reconstructor_stub)
        product->set_reconstructor((Graphics_Component_Reconstructor*)reconstructor_stub->construct());
}
