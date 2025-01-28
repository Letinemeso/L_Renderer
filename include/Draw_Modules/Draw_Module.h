#pragma once

#include <mat4x4.hpp>
#include <glew.h>

#include <Data_Structures/List.h>

#include <Builder_Stub.h>

#include <Module.h>

#include <Components/Graphics_Component.h>


namespace LR
{

    class Shader_Program;
    class Renderer;
    class Draw_Order_Controller;
    class Shader_Manager;


    class Draw_Module : public LEti::Module
    {
    public:
        INIT_VARIABLE(LR::Draw_Module, LEti::Module)

    protected:
        LR::Renderer* m_renderer = nullptr;
        Shader_Program* m_shader_program = nullptr;
        Draw_Order_Controller* m_draw_order_controller = nullptr;

    public:
        using Graphics_Component_List = LDS::List<Graphics_Component*>;

    protected:
        std::string m_draw_layer;

        unsigned int m_vertex_array = 0;

        Graphics_Component_List m_graphics_components;
        unsigned int m_vertices_amount = 0;

        unsigned int m_draw_mode = GL_TRIANGLES;

        bool m_should_recalculate_vertices_before_draw = false;
        bool m_visible = true;
        bool m_draw_on_update = true;

	public:
        Draw_Module();
        ~Draw_Module();

    public:
        inline void set_renderer(LR::Renderer* _ptr) { m_renderer = _ptr; }
        inline void set_shader_program(LR::Shader_Program* _ptr) { m_shader_program = _ptr; }

        inline LR::Renderer* renderer() const { return m_renderer; }

    public:
        void set_draw_layer(Draw_Order_Controller* _draw_order_controller, const std::string& _layer_name);
        void reset_draw_layer();

        inline Draw_Order_Controller* draw_order_controller() const { return m_draw_order_controller; }
        inline const std::string& draw_layer() const { return m_draw_layer; }

    public:
        inline unsigned int vertex_array() const { return m_vertex_array; }
        inline bool visible() const { return m_visible; }
        inline bool draw_on_update() const { return m_draw_on_update; }
        inline unsigned int draw_mode() const { return m_draw_mode; }

    public:
        inline void set_visible(bool _value) { m_visible = _value; }
        inline void set_draw_on_update(bool _value) { m_draw_on_update = _value; }
        inline void set_draw_mode(unsigned int _value) { m_draw_mode = _value; }

    public:
        void add_graphics_component(Graphics_Component* _ptr);
        void recalculate_vertices_amount();
        void bind_vertex_array() const;

    public:
        inline const Graphics_Component_List& graphics_components() const { return m_graphics_components; }
        inline unsigned int vertices_amount() const { return m_vertices_amount; }

        Graphics_Component* get_graphics_component_with_buffer_index(unsigned int _index);
        const Graphics_Component* get_graphics_component_with_buffer_index(unsigned int _index) const;

    protected:
        virtual void M_update_internal(float _dt);

    public:
        void update(float _dt) override;
        virtual void draw() const;

	};



    class Draw_Module_Stub : public LEti::Module_Stub
    {
    public:
        INIT_VARIABLE(LR::Draw_Module_Stub, LEti::Module_Stub)

        INIT_FIELDS
        ADD_FIELD(bool, visible)
        ADD_FIELD(std::string, draw_mode)
        ADD_FIELD(std::string, draw_layer)
        ADD_FIELD(std::string, shader_id)
        FIELDS_END

        INIT_CHILDS_LISTS
        ADD_CHILDS_LIST("Graphics_Component_Stub__*", &graphics_component_stubs)
        CHILDS_LISTS_END

    public:
        bool visible = true;
        std::string draw_mode = "GL_TRIANGLES";
        std::string draw_layer;
        std::string shader_id;

    public:
        Renderer* renderer = nullptr;
        Draw_Order_Controller* draw_order_controller = nullptr;
        Shader_Manager* shader_manager = nullptr;

    public:
        LV::Variable_Base::Childs_List graphics_component_stubs;

    protected:
        INIT_BUILDER_STUB(Draw_Module);

    private:
        void M_apply_draw_mode(Draw_Module* _product) const;

    public:
        ~Draw_Module_Stub();

    };

}
