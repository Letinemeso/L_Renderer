#include <Texture/Texture__Preloaded.h>

using namespace LR;


void Texture__Preloaded::prepare_to_draw()
{
    L_ASSERT(m_texture);
    m_texture->prepare_to_draw();
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Texture_Stub__Preloaded)

BUILDER_STUB_INITIALIZATION_FUNC(Texture_Stub__Preloaded)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    L_ASSERT(resources_manager_getter);
    const LV::Variable_Loader* resources_manager = resources_manager_getter();
    L_ASSERT(resources_manager);

    Texture__Default* preloaded_texture = resources_manager->get_variable<Texture__Default>(texture_resource_name);
    product->set_texture(preloaded_texture);
}
