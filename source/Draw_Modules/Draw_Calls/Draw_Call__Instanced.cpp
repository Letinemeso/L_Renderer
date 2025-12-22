#include <Draw_Modules/Draw_Calls/Draw_Call__Instanced.h>

#include <glew.h>
#include <Draw_Modules/Draw_Module.h>

using namespace LR;


void Draw_Call__Instanced::draw(const Draw_Module* _draw_module)
{
    L_ASSERT(m_instances_amount > 0);
    glDrawArraysInstanced(_draw_module->draw_mode(), 0, _draw_module->calculate_vertices_amount(), m_instances_amount);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Draw_Call_Stub__Instanced)

BUILDER_STUB_INITIALIZATION_FUNC(Draw_Call_Stub__Instanced)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    L_ASSERT(instances_amount > 0);

    product->set_instances_amount(instances_amount);
}
