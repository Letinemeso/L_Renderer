#pragma once

#include <Variable_Base.h>
#include <Builder_Stub.h>


namespace LR
{

    class Draw_Module;
    class Graphics_Component;


    class Graphics_Component_Reconstructor : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component_Reconstructor, LV::Variable_Base)

    protected:
        Draw_Module* m_draw_module = nullptr;
        Graphics_Component* m_graphics_component = nullptr;

    public:
        inline void inject_draw_module(Draw_Module* _ptr) { m_draw_module = _ptr; M_on_draw_module_injected(); }
        inline void inject_graphics_component(Graphics_Component* _ptr) { m_graphics_component = _ptr; M_on_graphics_component_injected(); }

    protected:
        virtual void M_on_draw_module_injected() { }
        virtual void M_on_graphics_component_injected() { }

    public:
        virtual void update(float _dt) = 0;

    };


    class Graphics_Component_Reconstructor_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component_Reconstructor_Stub, LV::Builder_Stub)

    };

}
