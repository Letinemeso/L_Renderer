#ifndef SHADER_TRANSFORM_COMPONENT_H
#define SHADER_TRANSFORM_COMPONENT_H

#include <mat4x4.hpp>

#include <Components/Texture.h>
#include <Shader/Shader_Components/Shader_Component.h>


namespace LR
{

    class Shader_Transform_Component : public Shader_Component
    {
    public:
        struct Vertex_Attribs
        {
            Vertex_Data coordinates = {0, 0};
            Vertex_Data colors = {1, 0};
            Vertex_Data texture_coordinates = {2, 0};
        };

    private:
        Vertex_Attribs m_vertex_attribs;

        std::string m_projection_matrix_uniform_name = "projection_matrix";
        std::string m_transform_matrix_uniform_name = "transform_matrix";
        std::string m_texture_uniform_name = "fp_in_texture";

        int m_projection_matrix_uniform = -1;
        int m_transform_matrix_uniform = -1;
        int m_texture_uniform = -1;

    public:
        void init(unsigned int _opengl_program_handle) override;

    public:
        void set_projection_matrix(const glm::mat4x4& _matrix) const;
        void set_transform_matrix(const glm::mat4x4& _matrix) const;
        void set_texture(const LR::Texture& _texture) const;

    public:
        inline const Vertex_Attribs& vertex_attribs() const { return m_vertex_attribs; }

    };

}

#endif // SHADER_TRANSFORM_COMPONENT_H
