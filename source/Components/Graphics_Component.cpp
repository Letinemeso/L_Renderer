#include <Components/Graphics_Component.h>

using namespace LR;


void Graphics_Component::prepare_to_draw() const
{
    if(m_on_prepare_func)
        m_on_prepare_func(this);
}





BUILDER_STUB_NULL_CONSTRUCTION_FUNC(Graphics_Component_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Graphics_Component_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    if(on_prepare_func)
        product->set_on_prepare_func(on_prepare_func);
}
