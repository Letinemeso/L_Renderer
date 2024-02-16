#pragma once

#include <mat4x4.hpp>
#include <glew.h>

#include <Data_Structures/List.h>

#include <Builder_Stub.h>

#include <Module.h>

#include <Components/Graphics_Component.h>


namespace LR
{

    class Renderer;



    class Draw_Module : public LEti::Module
    {
    public:
        INIT_VARIABLE(LR::Draw_Module, LEti::Module)

    protected:
        LR::Renderer* m_renderer = nullptr;

    public:
        using Graphics_Component_List = LDS::List<Graphics_Component*>;

    protected:
        unsigned int m_vertex_array = 0;

        Graphics_Component_List m_graphics_components;
        unsigned int m_vertices_amount = 0;

        bool m_visible = true;
        bool m_draw_on_update = true;

	public:
        Draw_Module();
        ~Draw_Module();

    public:
        inline void set_renderer(LR::Renderer* _renderer) { m_renderer = _renderer; }
        inline LR::Renderer* renderer() const { return m_renderer; }

    public:
        inline unsigned int vertex_array() const { return m_vertex_array; }
        inline bool visible() const { return m_visible; }
        inline bool draw_on_update() const { return m_draw_on_update; }

    public:
        inline void set_visible(bool _value) { m_visible = _value; }
        inline void set_draw_on_update(bool _value) { m_draw_on_update = _value; }

    public:
        void add_graphics_component(Graphics_Component* _ptr);

    public:
        inline const Graphics_Component_List& graphic_components() const { return m_graphics_components; }
        inline unsigned int vertices_amount() const { return m_vertices_amount; }

    public:
        void update(float _dt) override;

	};



    class Draw_Module_Stub : public LEti::Module_Stub
    {
    public:
        INIT_VARIABLE(LR::Draw_Module_Stub, LEti::Module_Stub)

        INIT_CHILDS_LISTS
        ADD_CHILDS_LIST("Graphics_Component_Stub__*", &graphics_component_stubs)
        CHILDS_LISTS_END

    public:
        LR::Renderer* renderer = nullptr;

    public:
        LV::Variable_Base::Childs_List graphics_component_stubs;

    protected:
        LV::Variable_Base* M_construct_product() const override;
        void M_init_constructed_product(LV::Variable_Base* _product) const override;

    public:
        ~Draw_Module_Stub();

    };

}
