#ifndef DRAW_MODULE_BASE_H
#define DRAW_MODULE_BASE_H

#include <mat4x4.hpp>

#include <Builder_Stub.h>

#include <Module.h>

#include <Picture/Graphic_Resources_Manager.h>
#include <Renderer/Renderer.h>
#include <Shader/Shader_Components/Shader_Transform_Component.h>
#include <Components/Texture.h>
#include <Components/Vertices.h>
#include <Components/Colors.h>


namespace LR
{

    class Draw_Module_Base : public LEti::Module
    {
    public:
        DECLARE_VARIABLE;

    protected:
        LR::Renderer* m_renderer = nullptr;

    protected:
        bool m_visible = true;

    protected:
        unsigned int m_vertex_array = 0;

	public:
		Draw_Module_Base();
        ~Draw_Module_Base();

    public:
        inline void set_visible(bool _visible) { m_visible = _visible; }
        inline void set_renderer(LR::Renderer* _renderer) { m_renderer = _renderer; }
        inline LR::Renderer* renderer() const { return m_renderer; }

    protected:
        virtual void M_draw() = 0;

    public:
        void update(float _dt) override;

    public:
        inline unsigned int vertex_array() const { return m_vertex_array; }
        inline bool visible() const { return m_visible; }

	};

    class Draw_Module_Base_Stub : public LEti::Module_Stub
    {
    public:
        DECLARE_VARIABLE;

    public:
        LR::Renderer* renderer = nullptr;

    protected:
        void M_init_constructed_product(LV::Variable_Base* _product) const override;

    };

}


#endif // DRAW_MODULE_BASE_H
