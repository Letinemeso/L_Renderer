#pragma once

#include <Uniform_Setters/Uniform_Setter.h>


namespace LR
{

    class Uniform_Setter__Transformation : public Uniform_Setter
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter__Transformation, LR::Uniform_Setter)

    public:
        void apply() const override;

    };


    class Uniform_Setter_Stub__Transformation : public Uniform_Setter_Stub
    {
    public:
        INIT_VARIABLE(LR::Uniform_Setter_Stub__Transformation, LR::Uniform_Setter_Stub)

    public:
        INIT_DEFAULT_BUILDER_STUB(Uniform_Setter__Transformation)

    };

}
