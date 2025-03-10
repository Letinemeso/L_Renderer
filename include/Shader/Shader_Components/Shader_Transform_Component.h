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

    private:
        std::string m_projection_matrix_uniform_name;
        std::string m_transform_matrix_uniform_name;

        int m_projection_matrix_uniform = -1;
        int m_transform_matrix_uniform = -1;

    public:
        inline void set_projection_matrix_uniform_name(const std::string& _value) { m_projection_matrix_uniform_name = _value; }
        inline void set_transform_matrix_uniform_name(const std::string& _value) { m_transform_matrix_uniform_name = _value; }

    public:
        void init(unsigned int _opengl_program_handle) override;

    public:
        void set_projection_matrix(const glm::mat4x4& _matrix) const;
        void set_transform_matrix(const glm::mat4x4& _matrix) const;

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
        FIELDS_END

    public:
        std::string projection_matrix_uniform_name;
        std::string transform_matrix_uniform_name;

    public:
        INIT_BUILDER_STUB(Shader_Transform_Component)

    };

}
