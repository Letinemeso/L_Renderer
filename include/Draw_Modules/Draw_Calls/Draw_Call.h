#pragma once

#include <Variable_Base.h>
#include <Builder_Stub.h>


namespace LR
{

    class Draw_Module;


    class Draw_Call : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Draw_Call, LV::Variable_Base)

    public:
        virtual void draw(const Draw_Module* _draw_module) = 0;

    };


    class Draw_Call_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Draw_Call_Stub, LV::Builder_Stub)

    public:
        INIT_BUILDER_STUB(Draw_Call)

    };

}
