#ifndef __SHADER
#define __SHADER

#include <iostream>
#include <string>

#include <glew.h>
#include <mat4x4.hpp>

#include <Data_Structures/Map.h>
#include <L_Debug/L_Debug.h>

#include <Components/Texture.h>


namespace LR
{

	class Shader
    {
    public:
        struct Vertex_Attribs
        {
            struct Vertex_Data
            {
                unsigned int index = 0;
                unsigned int floats_per_vertex = 0;
            };

            Vertex_Data coordinates = {0, 0};
            Vertex_Data colors = {1, 0};
            Vertex_Data texture_coordinates = {3, 0};
        };

	private:
        unsigned int m_vertex_shader = 0, m_fragment_shader = 0;
        unsigned int m_program = 0;

    private:
        Vertex_Attribs m_vertex_attribs;
        LDS::Map<std::string, int> m_uniform_matrices;

        std::string m_projection_matrix_uniform_name = "projection_matrix";
        std::string m_transform_matrix_uniform_name = "transform_matrix";
        std::string m_texture_uniform_name = "fp_in_texture";
        int m_projection_matrix_uniform = -1, m_transform_matrix_uniform = -1, m_texture_uniform = -1;

    public:
        Shader();
        Shader(Shader&& _other);
        void operator=(Shader&& _other);
        Shader(const Shader&) = delete;
        void operator=(const Shader&) = delete;

        ~Shader();

    private:
        void M_shader_debug(unsigned int _shader) const;
        void M_program_debug(unsigned int _program) const;

    private:
        void M_verify_vertex_attribs();
        void M_extract_uniforms_data();

	public:
        void init(const std::string& _vertex_shader_source, const std::string& _fragment_shader_source);

    public:
        void set_matrix_uniform(const glm::mat4x4& _matrix, int _uniform_location) const;

        void set_projection_matrix(const glm::mat4x4& _matrix) const;
        void set_transform_matrix(const glm::mat4x4& _matrix) const;
        void set_texture(const LR::Texture& _texture) const;

    public:
        int get_matrix_uniform_location(const std::string& _name) const;

    public:
        inline const Vertex_Attribs& vertex_attribs() const { return m_vertex_attribs; }

	};

}

#endif
