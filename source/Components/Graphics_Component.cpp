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



void Graphics_Component::prepare() const
{
    if(m_reconstructor)
        m_reconstructor->reconstruct_graphics_component();

    m_buffer.bind();

    if(m_on_prepare_func)
        m_on_prepare_func(this);
}





Graphics_Component_Stub::~Graphics_Component_Stub()
{
    delete[] data;
    delete reconstructor_stub;
}



LV::Variable_Base* Graphics_Component_Stub::M_construct_product() const
{
    return new Graphics_Component;
}

void Graphics_Component_Stub::M_init_constructed_product(LV::Variable_Base* _product) const
{
    LV::Builder_Stub::M_init_constructed_product(_product);

    Graphics_Component* product = (Graphics_Component*)_product;

    L_ASSERT(data);
    L_ASSERT(data_size > 0);
    L_ASSERT(floats_per_vertex > 0);

    product->buffer().free_memory();
    product->buffer().allocate_memory(data_size);
    product->buffer().copy_array(data, data_size);
    product->buffer().setup_buffer(attribute_index, floats_per_vertex);

    if(on_prepare_func)
        product->set_on_prepare_func(on_prepare_func);

    if(reconstructor_stub)
        product->set_reconstructor((Graphics_Component_Reconstructor*)reconstructor_stub->construct());
}
