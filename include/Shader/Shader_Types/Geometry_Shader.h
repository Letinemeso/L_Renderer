#pragma once

#include <Shader/Shader_Types/Shader.h>


namespace LR
{

    class Geometry_Shader : public Shader
    {
    private:
        inline unsigned int shader_type() const override { return GL_GEOMETRY_SHADER; }

    };

}
