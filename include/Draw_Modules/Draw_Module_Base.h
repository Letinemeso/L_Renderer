#ifndef DRAW_MODULE_BASE_H
#define DRAW_MODULE_BASE_H

#include <mat4x4.hpp>

#include <Object_System/Builder_Stub.h>

#include <Components/Texture.h>
#include <Components/Vertices.h>
#include <Components/Colors.h>


namespace LR
{

    class Draw_Module_Base_Stub : public LEti::Builder_Stub
    {
    public:
        DECLARE_VARIABLE;

    public:
        virtual ~Draw_Module_Base_Stub() { }

    };

    class Draw_Module_Base : public LV::Variable_Base
    {
    public:
        DECLARE_VARIABLE;

    protected:
        unsigned int m_vertex_array = 0;
        glm::mat4x4 m_transform_matrix;

        bool m_visible = true;

    protected:
        LR::Texture m_texture;
        LR::Vertices m_vertices;
        LR::Colors m_colors;

	public:
		Draw_Module_Base();
        virtual ~Draw_Module_Base();

    public:
        inline void set_visible(bool _visible) { m_visible = _visible; }

    public:
        virtual void update(const glm::mat4x4& _matrix);

    public:
        inline LR::Texture& texture() { return m_texture; }
        inline LR::Vertices& vertices() { return m_vertices; }
        inline LR::Colors& colors() { return m_colors; }
        inline const LR::Texture& texture() const { return m_texture; }
        inline const LR::Vertices& vertices() const { return m_vertices; }
        inline const LR::Colors& colors() const { return m_colors; }

    public:
        inline const glm::mat4x4& transform_matrix() const { return m_transform_matrix; }
        inline unsigned int vertex_array() const { return m_vertex_array; }
        inline bool visible() const { return m_visible; }

        inline virtual unsigned int gl_draw_mode() const = 0;  //  GL_TRIANGLES, GL_LINES, etc

	};

}


#endif // DRAW_MODULE_BASE_H
