#include <Components/Graphics_Component.h>

using namespace LR;


INIT_FIELDS(LR::Graphics_Component, LV::Variable_Base)
FIELDS_END


Graphics_Component::Graphics_Component()
{

}

Graphics_Component::~Graphics_Component()
{

}



void Graphics_Component::prepare() const
{
    m_buffer.bind();

    if(m_on_prepare_func)
        m_on_prepare_func(this);
}





INIT_FIELDS(LR::Graphics_Component_Stub, LV::Builder_Stub)

ADD_FIELD(unsigned int, attribute_index)
ADD_FIELD(unsigned int, floats_per_vertex)

ADD_FIELD(float*, data)
ADD_FIELD(unsigned int, data_size)

FIELDS_END


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
}
