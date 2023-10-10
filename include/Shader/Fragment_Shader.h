#ifndef FRAGMENT_SHADER_H
#define FRAGMENT_SHADER_H

#include <Shader/Shader.h>


namespace LR
{

    class Fragment_Shader : public Shader
    {
    public:
        inline unsigned int shader_type() const override { return GL_FRAGMENT_SHADER; }

    };

}

#endif // FRAGMENT_SHADER_H
