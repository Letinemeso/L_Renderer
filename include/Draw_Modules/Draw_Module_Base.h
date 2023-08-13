#ifndef DRAW_MODULE_BASE_H
#define DRAW_MODULE_BASE_H

#include <mat4x4.hpp>

#include <Builder_Stub.h>

#include <Module.h>

#include <Renderer/Renderer.h>
#include <Components/Texture.h>
#include <Components/Vertices.h>
#include <Components/Colors.h>


namespace LR
{

    class Draw_Module_Base_Stub : public LV::Builder_Stub
    {
    public:
        DECLARE_VARIABLE;

    public:
        LR::Renderer* renderer = nullptr;

    public:
        virtual ~Draw_Module_Base_Stub() { }

    protected:
        void M_init_constructed_product(LV::Variable_Base* _product) const override;

    };

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
        LR::Texture m_texture;
        LR::Vertices m_vertices;
        LR::Colors m_colors;

	public:
		Draw_Module_Base();
        ~Draw_Module_Base();

    public:
        inline void set_visible(bool _visible) { m_visible = _visible; }
        inline void set_renderer(LR::Renderer* _renderer) { m_renderer = _renderer; }
        inline LR::Renderer* renderer() const { return m_renderer; }

    public:
        void update() override;

    public:
        inline LR::Texture& texture() { return m_texture; }
        inline LR::Vertices& vertices() { return m_vertices; }
        inline LR::Colors& colors() { return m_colors; }
        inline const LR::Texture& texture() const { return m_texture; }
        inline const LR::Vertices& vertices() const { return m_vertices; }
        inline const LR::Colors& colors() const { return m_colors; }

    public:
        inline unsigned int vertex_array() const { return m_vertex_array; }
        inline bool visible() const { return m_visible; }

        inline virtual unsigned int gl_draw_mode() const = 0;  //  GL_TRIANGLES, GL_LINES, etc

	};

}


#endif // DRAW_MODULE_BASE_H
