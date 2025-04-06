#pragma once

#include <Stuff/Function_Wrapper.h>

#include <Object_Constructor.h>

#include <Resources_Manager.h>

#include <Renderer/Renderer.h>
#include <Draw_Order_Controller/Draw_Order_Controller.h>
#include <Shader/Shader_Manager.h>


namespace LR
{
    void register_types(LV::Object_Constructor& _object_constructor,
                        const LST::Function<const LEti::Resources_Manager*()>& _resources_manager_getter,
                        LR::Renderer& _renderer,
                        LR::Draw_Order_Controller* _draw_order_controller,
                        const LST::Function<const LR::Shader_Manager*()>& _shader_manager_getter);
}
