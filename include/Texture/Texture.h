#pragma once

#include <L_Debug/L_Debug.h>

#include <Variable_Base.h>
#include <Builder_Stub.h>


namespace LR
{

    class Texture : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Texture, LV::Variable_Base)

    public:
        virtual void prepare_to_draw() = 0;

    };


    class Texture_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Texture_Stub, LV::Builder_Stub)

    public:
        INIT_BUILDER_STUB(Texture)

    };

}
