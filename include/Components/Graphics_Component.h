#pragma once

#include <Stuff/Function_Wrapper.h>

#include <Variable_Base.h>
#include <Builder_Stub.h>

#include <Components/Graphics_Component_Reconstructor.h>


namespace LR
{

    class Draw_Module;


    class Graphics_Component : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component, LV::Variable_Base)

    private:
        LST::Function<void(const Graphics_Component*)> m_on_prepare_func;

    protected:
        Draw_Module* m_parent_draw_module = nullptr;

    protected:
        virtual void M_on_parent_draw_module_set() { }

    public:
        inline void set_on_prepare_func(const LST::Function<void(const Graphics_Component*)>& _func) { m_on_prepare_func = _func; }
        inline void set_parent_draw_module(Draw_Module* _ptr) { m_parent_draw_module = _ptr; M_on_parent_draw_module_set(); }

    public:
        virtual unsigned int layout_index() const = 0;
        virtual unsigned int vertices_amount() const = 0;
        virtual unsigned int required_compute_shader_invocations() const = 0;
        virtual void setup_buffer() const = 0;
        virtual void update(float _dt) = 0;
        virtual void prepare_to_draw() const;
        virtual void bind_for_computation() const = 0;

    };



    class Graphics_Component_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component_Stub, LV::Builder_Stub)

    public:
        LST::Function<void(const Graphics_Component*)> on_prepare_func;

    protected:
        INIT_BUILDER_STUB(Graphics_Component)

    };

}
