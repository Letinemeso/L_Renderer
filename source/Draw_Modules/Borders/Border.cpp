#include <Draw_Modules/Borders/Border.h>

#include <Components/Graphics_Component__Default.h>

using namespace LR;


void Border::init(const LV::Variable_Base::Childs_List& _components_list)
{
    if(m_searched_layout_index == 0xFFFFFFFF)
        return;

    const Graphics_Component_Stub__Default* searched_component = nullptr;
    for(LV::Variable_Base::Childs_List::Const_Iterator it = _components_list.begin(); !it.end_reached(); ++it)
    {
        L_ASSERT(LV::cast_variable<Graphics_Component_Stub>(it->child_ptr));
        const Graphics_Component_Stub* component = (Graphics_Component_Stub*)it->child_ptr;

        const Graphics_Component_Stub__Default* default_component = LV::cast_variable<Graphics_Component_Stub__Default>(component);
        if(!default_component)
            continue;
        if(default_component->layout_index != m_searched_layout_index)
            continue;

        searched_component = default_component;
        break;
    }

    L_ASSERT(searched_component);
    L_ASSERT(searched_component->floats_per_vertex == 3);

    init(searched_component->select_data());
}
