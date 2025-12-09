#pragma once

#include <mat4x4.hpp>

#include <Components/Graphics_Component__Texture.h>
#include <Shader/Shader_Components/Shader_Component.h>


namespace LR
{

    class Shader_Rotation_Matrix_Component : public Shader_Component
    {
    public:
        INIT_VARIABLE(LR::Shader_Rotation_Matrix_Component, LR::Shader_Component)

    private:
        std::string m_uniform_name;

        int m_uniform = -1;

    public:
        inline void set_uniform_name(const std::string& _value) { m_uniform_name = _value; }

    public:
        void init(unsigned int _opengl_program_handle) override;

    public:
        void set_rotation_matrix(const glm::mat4x4& _matrix) const;

    public:
        void update(const Draw_Module* _draw_module) override;

    };


    class Shader_Rotation_Matrix_Component_Stub : public Predefined_Shader_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Shader_Rotation_Matrix_Component_Stub, LR::Predefined_Shader_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, uniform_name)
        FIELDS_END

    public:
        std::string uniform_name = "rotation_matrix_uniform";

    public:
        INIT_BUILDER_STUB(Shader_Rotation_Matrix_Component)

    };

}
