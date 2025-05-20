#include <Components/Graphics_Component__Proxy.h>

#include <Object.h>

#include <Draw_Modules/Draw_Module.h>

using namespace LR;


void Graphics_Component__Proxy::update(float /*_dt*/)
{
    if(m_linked_graphics_component)
        return;

    L_ASSERT(m_parent_draw_module);
    const LEti::Object* parent_object = m_parent_draw_module->parent_object();
    const LR::Draw_Module* linked_module = parent_object->get_module_of_type<LR::Draw_Module>(m_linked_draw_module_index);
    m_linked_graphics_component = linked_module->get_graphics_component_with_buffer_index(m_linked_buffer_index);
    L_ASSERT(m_linked_graphics_component);
}

void Graphics_Component__Proxy::prepare_to_draw() const
{
    Parent_Type::prepare_to_draw();

    if(m_linked_graphics_component)
        m_linked_graphics_component->prepare_to_draw();
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Graphics_Component_Stub__Proxy)

BUILDER_STUB_INITIALIZATION_FUNC(Graphics_Component_Stub__Proxy)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_linked_draw_module_index(linked_draw_module_index);
    product->set_linked_buffer_index(linked_buffer_index);
}
