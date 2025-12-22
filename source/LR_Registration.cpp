#include <LR_Registration.h>

#include <Components/Graphics_Component__Default.h>
#include <Components/Graphics_Component__Texture.h>
#include <Components/Graphics_Component__Proxy.h>
#include <Draw_Modules/Draw_Module.h>
#include <Draw_Modules/Draw_Calls/Draw_Call__Default.h>
#include <Resources/Font.h>
#include <Resources/Picture.h>
#include <Shader/Shader_Components/Shader_Component.h>
#include <Shader/Shader_Components/Shader_Texture_Component.h>
#include <Shader/Shader_Components/Shader_Transform_Component.h>
#include <Shader/Shader_Components/Shader_Window_Size_Component.h>
#include <Shader/Shader_Components/Shader_RNG_Component.h>
#include <Shader/Shader_Components/Shader_Position_Getter_Component.h>
#include <Shader/Shader_Components/Shader_Dt_Component.h>
#include <Shader/Shader_Components/Shader_Rotation_Matrix_Component.h>
#include <Shader/Shader.h>
#include <Shader/Shader_Program.h>
#include <Shader/Shader_Manager.h>
#include <Texture/Texture.h>
#include <Texture/Texture__Default.h>
#include <Texture/Texture__Preloaded.h>
#include <Texture/Texture__Frame_Buffer.h>
#include <Uniform_Setters/Uniform_Setter.h>
#include <Draw_Rule/Draw_Rule.h>

using namespace LR;


void LR::register_types(LV::Object_Constructor& _object_constructor,
                        const LST::Function<const LEti::Resources_Manager*()>& _resources_manager_getter,
                        LR::Renderer& _renderer,
                        LR::Draw_Order_Controller* _draw_order_controller,
                        const LST::Function<const LR::Shader_Manager*()>& _shader_manager_getter,
                        const LST::Function<float()>& _get_dt_func
                        )
{
    L_ASSERT(_resources_manager_getter);
    L_ASSERT(_shader_manager_getter);

    LV::Object_Constructor* object_constructor = &_object_constructor;
    LR::Renderer* renderer = &_renderer;

    _object_constructor.register_type<LR::Graphics_Component_Stub__Default>();

    _object_constructor.register_type<LR::Graphics_Component_Stub__Texture>();

    _object_constructor.register_type<LR::Graphics_Component_Stub__Proxy>();

    _object_constructor.register_type<LR::Draw_Module_Stub>().override_initialization_func([renderer, _draw_order_controller, _shader_manager_getter](LV::Variable_Base* _product)
    {
        LR::Draw_Module_Stub* product = (LR::Draw_Module_Stub*)_product;

        product->renderer = renderer;
        product->draw_order_controller = _draw_order_controller;
        product->shader_manager = _shader_manager_getter();
    });

    _object_constructor.register_type<LR::Draw_Call_Stub__Default>();

    _object_constructor.register_type<LR::Letter_Data>();

    _object_constructor.register_type<LR::Font_Stub>();

    _object_constructor.register_type<LR::Picture_Stub>();

    _object_constructor.register_type<LR::Shader_Component_Stub>();

    _object_constructor.register_type<LR::Shader_Texture_Component_Stub>();

    _object_constructor.register_type<LR::Shader_Transform_Component_Stub>();

    _object_constructor.register_type<LR::Shader_Rotation_Matrix_Component_Stub>();

    _object_constructor.register_type<LR::Shader_Window_Size_Component_Stub>();

    _object_constructor.register_type<LR::Shader_RNG_Component_Stub>();

    _object_constructor.register_type<LR::Shader_Position_Getter_Component_Stub>();

    _object_constructor.register_type<LR::Shader_Dt_Componen_Stub>().override_initialization_func([_get_dt_func](LV::Variable_Base* _product)
    {
        LR::Shader_Dt_Componen_Stub* product = (LR::Shader_Dt_Componen_Stub*)_product;

        product->dt_getter = _get_dt_func;
    });

    _object_constructor.register_type<LR::Shader_Stub>();

    _object_constructor.register_type<LR::Shader_Program_Stub>();

    _object_constructor.register_type<LR::Shader_Manager_Stub>();

    _object_constructor.register_type<LR::Texture_Stub>();

    _object_constructor.register_type<LR::Texture_Stub__Default>().override_initialization_func([_resources_manager_getter](LV::Variable_Base* _product)
    {
        LR::Texture_Stub__Default* product = (LR::Texture_Stub__Default*)_product;

        product->resources_manager_getter = _resources_manager_getter;
    });

    _object_constructor.register_type<LR::Texture_Stub__Preloaded>().override_initialization_func([_resources_manager_getter](LV::Variable_Base* _product)
    {
        LR::Texture_Stub__Preloaded* product = (LR::Texture_Stub__Preloaded*)_product;

        product->resources_manager_getter = _resources_manager_getter;
    });

    _object_constructor.register_type<LR::Texture_Stub__Frame_Buffer>();

    _object_constructor.register_type<LR::Uniform_Setter_Stub__Float>();

    _object_constructor.register_type<LR::Uniform_Setter_Stub__Int>();

    _object_constructor.register_type<LR::Uniform_Setter_Stub__UInt>();

    _object_constructor.register_type<LR::Uniform_Setter_Stub__Vec2>();

    _object_constructor.register_type<LR::Uniform_Setter_Stub__Vec3>();

    _object_constructor.register_type<LR::Draw_Rule_Stub>();
}
