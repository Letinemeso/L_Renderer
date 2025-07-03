#pragma once

#include <Components/Graphics_Component.h>


namespace LR
{

    class Graphics_Component__Proxy : public Graphics_Component
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component__Proxy, LR::Graphics_Component)

    private:
        unsigned int m_linked_draw_module_index = 0xFFFFFFFF;
        unsigned int m_linked_buffer_index = 0xFFFFFFFF;

    private:
        const Graphics_Component* m_linked_graphics_component = nullptr;

    public:
        inline void set_linked_draw_module_index(unsigned int _value) { m_linked_draw_module_index = _value; }
        inline void set_linked_buffer_index(unsigned int _value) { m_linked_buffer_index = _value; }

        inline void set_linked_graphics_component(const Graphics_Component* _ptr) { m_linked_graphics_component = _ptr; }

    public:
        void link_module_manually(const LR::Draw_Module* _module);

    public:
        unsigned int layout_index() const override;
        unsigned int vertices_amount() const override;
        unsigned int required_compute_shader_invocations() const override;
        void setup_buffer() const override;
        void update(float _dt) override;
        void prepare_to_draw() const override;
        void bind_for_computation() const override;

    };


    class Graphics_Component_Stub__Proxy : public Graphics_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component_Stub__Proxy, LR::Graphics_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(unsigned int, linked_draw_module_index)
        ADD_FIELD(unsigned int, linked_buffer_index)
        FIELDS_END

    public:
        unsigned int linked_draw_module_index = 0xFFFFFFFF;
        unsigned int linked_buffer_index = 0xFFFFFFFF;

    public:
        INIT_BUILDER_STUB(Graphics_Component__Proxy)

    };

}
