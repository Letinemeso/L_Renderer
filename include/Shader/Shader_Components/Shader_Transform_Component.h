#ifndef SHADER_TRANSFORM_COMPONENT_H
#define SHADER_TRANSFORM_COMPONENT_H

#include <Shader/Shader_Components/Shader_Component.h>


namespace LR
{

    class Shader_Transform_Component : public Shader_Component
    {
    private:


    public:
        void init(unsigned int _opengl_program_handle) override;

    public:
        void update() const override;

    };

}

#endif // SHADER_TRANSFORM_COMPONENT_H
