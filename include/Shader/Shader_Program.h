#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <iostream>
#include <string>

#include <glew.h>
#include <mat4x4.hpp>

#include <Data_Structures/Map.h>
#include <Data_Structures/List.h>
#include <L_Debug/L_Debug.h>

#include <Shader/Shader_Types/Shader.h>
#include <Components/Texture.h>


namespace LR
{

    class Shader_Program
    {
    public:
        struct Vertex_Attribs
        {
            struct Vertex_Data
            {
                Vertex_Data(unsigned int _index, unsigned int _floats_per_vertex) : index(_index), floats_per_vertex(_floats_per_vertex) { }

                unsigned int index = 0;
                unsigned int floats_per_vertex = 0;
            };

            Vertex_Data coordinates = {0, 0};
            Vertex_Data colors = {1, 0};
            Vertex_Data texture_coordinates = {2, 0};
        };

    private:
        unsigned int m_program_handle = 0;
        LDS::List<Shader*> m_shader_objects;

    private:
        Vertex_Attribs m_vertex_attribs;
        LDS::Map<std::string, int> m_uniform_matrices;
        LDS::Map<std::string, int> m_uniform_vectors;

        std::string m_projection_matrix_uniform_name = "projection_matrix";
        std::string m_transform_matrix_uniform_name = "transform_matrix";
        std::string m_texture_uniform_name = "fp_in_texture";
        int m_projection_matrix_uniform = -1, m_transform_matrix_uniform = -1, m_texture_uniform = -1;

    public:
        Shader_Program(const Shader_Program&) = delete;
        void operator=(const Shader_Program&) = delete;

    public:
        Shader_Program();
        Shader_Program(Shader_Program&& _other);
        void operator=(Shader_Program&& _other);

        ~Shader_Program();

    private:
        bool M_uniform_is_block(const std::string& _uniform_name) const;

    private:
        void M_verify_vertex_attribs();
        void M_extract_uniforms_data();

    private:
        void M_debug() const;

    public:
        void reset();
        void add_shader(Shader* _shader);
        void init();

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

#endif // SHADER_PROGRAM_H
