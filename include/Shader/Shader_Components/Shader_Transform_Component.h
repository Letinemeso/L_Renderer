#pragma once

#include <mat4x4.hpp>

#include <Components/Graphics_Component__Texture.h>
#include <Shader/Shader_Components/Shader_Component.h>


namespace LR
{

    class Shader_Transform_Component : public Shader_Component
    {
    public:
        INIT_VARIABLE(LR::Shader_Transform_Component, LR::Shader_Component)

    public:
        struct Vertex_Attribs
        {
            Vertex_Data coordinates = {0, 0};
            Vertex_Data colors = {1, 0};
            Vertex_Data texture_coordinates = {2, 0};
        };

    private:
        Vertex_Attribs m_vertex_attribs;

        std::string m_projection_matrix_uniform_name;
        std::string m_transform_matrix_uniform_name;
        std::string m_texture_uniform_name;
        std::string m_coords_input_buffer_name;
        std::string m_colors_input_buffer_name;
        std::string m_texture_coords_input_buffer_name;

        int m_projection_matrix_uniform = -1;
        int m_transform_matrix_uniform = -1;
        int m_texture_uniform = -1;

    public:
        inline void set_projection_matrix_uniform_name(const std::string& _value) { m_projection_matrix_uniform_name = _value; }
        inline void set_transform_matrix_uniform_name(const std::string& _value) { m_transform_matrix_uniform_name = _value; }
        inline void set_texture_uniform_name(const std::string& _value) { m_texture_uniform_name = _value; }
        inline void set_coords_input_buffer_name(const std::string& _value) { m_coords_input_buffer_name = _value; }
        inline void set_colors_input_buffer_name(const std::string& _value) { m_colors_input_buffer_name = _value; }
        inline void set_texture_coords_input_buffer_name(const std::string& _value) { m_texture_coords_input_buffer_name = _value; }

    public:
        void init(unsigned int _opengl_program_handle) override;

    public:
        void set_projection_matrix(const glm::mat4x4& _matrix) const;
        void set_transform_matrix(const glm::mat4x4& _matrix) const;

        void prepare_texture_uniform() const;

    public:
        inline const Vertex_Attribs& vertex_attribs() const { return m_vertex_attribs; }

    public:
        void update(const Draw_Module* _draw_module) override;

    };


    class Shader_Transform_Component_Stub : public Shader_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Transform_Component_Stub, LR::Shader_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, projection_matrix_uniform_name)
        ADD_FIELD(std::string, transform_matrix_uniform_name)
        ADD_FIELD(std::string, texture_uniform_name)
        ADD_FIELD(std::string, coords_input_buffer_name)
        ADD_FIELD(std::string, colors_input_buffer_name)
        ADD_FIELD(std::string, texture_coords_input_buffer_name)
        FIELDS_END

    public:
        std::string projection_matrix_uniform_name = "projection_matrix";
        std::string transform_matrix_uniform_name = "transform_matrix";
        std::string texture_uniform_name = "fp_in_texture";
        std::string coords_input_buffer_name = "vs_in_pos";
        std::string colors_input_buffer_name = "vs_in_colors";
        std::string texture_coords_input_buffer_name = "vs_in_tex_coords";

    public:
        INIT_BUILDER_STUB(Shader_Transform_Component);

    };

}
