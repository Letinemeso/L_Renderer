#pragma once

#include <Draw_Modules/Draw_Calls/Draw_Call.h>


namespace LR
{

    class Draw_Call__Default : public LR::Draw_Call
    {
    public:
        INIT_VARIABLE(LR::Draw_Call__Default, LR::Draw_Call)

    public:
        void draw(const Draw_Module* _draw_module) override;

    };


    class Draw_Call_Stub__Default : public LR::Draw_Call_Stub
    {
    public:
        INIT_VARIABLE(LR::Draw_Call_Stub__Default, LR::Draw_Call_Stub)

    public:
        INIT_DEFAULT_BUILDER_STUB(Draw_Call__Default)

    };

}
