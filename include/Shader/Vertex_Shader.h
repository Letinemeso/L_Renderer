#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include <Shader/Shader.h>


namespace LR
{

    class Vertex_Shader : public Shader
    {
    public:
        inline unsigned int shader_type() const override { return GL_VERTEX_SHADER; }

    };

}

#endif // VERTEX_SHADER_H
