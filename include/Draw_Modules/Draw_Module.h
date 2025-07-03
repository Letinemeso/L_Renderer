#pragma once

#include <mat4x4.hpp>

#include <Data_Structures/List.h>

#include <Builder_Stub.h>

#include <Module.h>

#include <Components/Graphics_Component.h>
#include <Uniform_Setters/Uniform_Setter.h>


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
        struct Compute_Shader_Work_Groups_Sizes
        {
            unsigned int x = 0;
            unsigned int y = 0;
            unsigned int z = 0;
        };

    protected:
        LR::Renderer* m_renderer = nullptr;
        Shader_Program* m_rendering_shader_program = nullptr;
        Shader_Program* m_compute_shader_program = nullptr;
        Compute_Shader_Work_Groups_Sizes m_compute_shader_work_group_sizes;
        Draw_Order_Controller* m_draw_order_controller = nullptr;

    public:
        using Graphics_Component_List = LDS::List<Graphics_Component*>;
        using Uniform_Setter_List = LDS::List<Uniform_Setter*>;

    protected:
        std::string m_draw_layer;
        bool m_should_update_draw_layer = false;

        unsigned int m_vertex_array = 0;

        Graphics_Component_List m_graphics_components;
        Uniform_Setter_List m_graphics_uniform_setters;
        Uniform_Setter_List m_compute_uniform_setters;

        unsigned int m_draw_mode = 0;

        bool m_visible = true;
        bool m_draw_on_update = true;

	public:
        Draw_Module();
        ~Draw_Module();

    public:
        inline void set_renderer(Renderer* _ptr) { m_renderer = _ptr; }

        inline Renderer* renderer() const { return m_renderer; }
        inline Shader_Program* rendering_shader_program() const { return m_rendering_shader_program; }
        inline Shader_Program* compute_shader_program() const { return m_compute_shader_program; }

    public:
        void set_rendering_shader_program(Shader_Program* _ptr);
        void set_compute_shader_program(Shader_Program* _ptr);

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
        void add_graphics_uniform_setter(Uniform_Setter* _ptr);
        void add_compute_uniform_setter(Uniform_Setter* _ptr);
        void bind_vertex_array() const;

    public:
        inline const Graphics_Component_List& graphics_components() const { return m_graphics_components; }
        inline const Uniform_Setter_List& graphics_uniform_setters_list() const { return m_graphics_uniform_setters; }
        inline const Uniform_Setter_List& compute_uniform_setters_list() const { return m_compute_uniform_setters; }

        Graphics_Component* get_graphics_component_with_buffer_index(unsigned int _index);
        const Graphics_Component* get_graphics_component_with_buffer_index(unsigned int _index) const;

        Uniform_Setter* get_graphics_uniform_setter_with_name(const std::string& _name) const;
        Uniform_Setter* get_compute_uniform_setter_with_name(const std::string& _name) const;

    protected:
        void M_update_compute_shader_work_groups_sizes();
        void M_update_draw_layer_if_needed();
        unsigned int M_calculate_necessary_computer_shader_incovations() const;
        unsigned int M_calculate_necessary_work_groups(unsigned int _work_group_size) const;
        void M_dispatch_compute_shader_if_any() const;
        unsigned int M_calculate_vertices_amount() const;
        virtual void M_update_internal(float _dt);
        virtual void M_draw_internal() const;
        void M_apply_graphics_uniform_setters() const;
        void M_apply_compute_uniform_setters() const;

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
        ADD_FIELD(bool, draw_on_update)
        ADD_FIELD(std::string, draw_mode)
        ADD_FIELD(std::string, draw_layer)
        ADD_FIELD(std::string, rendering_shader_id)
        ADD_FIELD(std::string, compute_shader_id)
        FIELDS_END

        INIT_CHILDS_LISTS
        ADD_CHILDS_LIST("Graphics_Component_Stub__*", &graphics_component_stubs)
        ADD_CHILDS_LIST("Graphics_Uniform_Setter_Stub__*", &graphics_uniform_setter_stubs)
        ADD_CHILDS_LIST("Compute_Uniform_Setter_Stub__*", &compute_uniform_setter_stubs)
        CHILDS_LISTS_END

    public:
        bool visible = true;
        bool draw_on_update = true;
        std::string draw_mode = "GL_TRIANGLES";
        std::string draw_layer;
        std::string rendering_shader_id;
        std::string compute_shader_id;

    public:
        Renderer* renderer = nullptr;
        Draw_Order_Controller* draw_order_controller = nullptr;
        const Shader_Manager* shader_manager = nullptr;

    public:
        LV::Variable_Base::Childs_List graphics_component_stubs;
        LV::Variable_Base::Childs_List graphics_uniform_setter_stubs;
        LV::Variable_Base::Childs_List compute_uniform_setter_stubs;

    protected:
        INIT_BUILDER_STUB(Draw_Module)

    private:
        void M_apply_draw_mode(Draw_Module* _product) const;

    public:
        ~Draw_Module_Stub();

    };

}
