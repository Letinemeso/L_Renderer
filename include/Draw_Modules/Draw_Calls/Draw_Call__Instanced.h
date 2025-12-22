#pragma once

#include <Draw_Modules/Draw_Calls/Draw_Call.h>


namespace LR
{

    class Draw_Call__Instanced : public LR::Draw_Call
    {
    public:
        INIT_VARIABLE(LR::Draw_Call__Instanced, LR::Draw_Call)

    private:
        unsigned int m_instances_amount = 0;

    public:
        inline void set_instances_amount(unsigned int _value) { m_instances_amount = _value; }

    public:
        void draw(const Draw_Module* _draw_module) override;

    };


    class Draw_Call_Stub__Instanced : public LR::Draw_Call_Stub
    {
    public:
        INIT_VARIABLE(LR::Draw_Call_Stub__Instanced, LR::Draw_Call_Stub)

        INIT_FIELDS
        ADD_FIELD(unsigned int, instances_amount)
        FIELDS_END

    public:
        unsigned int instances_amount = 0;

    public:
        INIT_BUILDER_STUB(Draw_Call__Instanced)

    };

}
