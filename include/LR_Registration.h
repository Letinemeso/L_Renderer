#pragma once

#include <Stuff/Function_Wrapper.h>

#include <Object_Constructor.h>

#include <Variable_Loader.h>

#include <Renderer/Renderer.h>
#include <Draw_Order_Controller/Draw_Order_Controller.h>
#include <Shader/Shader_Manager.h>


namespace LR
{
    void register_types(LV::Object_Constructor& _object_constructor,
                        const LST::Function<const LV::Variable_Loader*()>& _resources_manager_getter,
                        LR::Renderer& _renderer,
                        LR::Draw_Order_Controller* _draw_order_controller,
                        const LST::Function<const LR::Shader_Manager*()>& _shader_manager_getter,
                        const LST::Function<float()>& _get_dt_func = {}
                    );
}
