#pragma once

#include <Data_Structures/Vector.h>

#include <Variable_Base.h>
#include <Builder_Stub.h>


namespace LR
{

    class Draw_Rule : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Draw_Rule, LV::Variable_Base)

    private:
        unsigned int m_vertex_array = 0;

    public:
        Draw_Rule();
        ~Draw_Rule();

    public:
        void enable_attribute_array(unsigned int _index, unsigned int _floats_per_vertex);
        void disable_attribute_array(unsigned int _index);

    public:
        void use() const;

    };


    class Draw_Rule_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Draw_Rule_Stub, LV::Builder_Stub)

        INIT_FIELDS
        ADD_FIELD(LDS::Vector<unsigned int>, active_attribute_arrays)
        ADD_FIELD(LDS::Vector<unsigned int>, floats_per_vertex)
        FIELDS_END

    public:
        LDS::Vector<unsigned int> active_attribute_arrays;
        LDS::Vector<unsigned int> floats_per_vertex;

    public:
        INIT_BUILDER_STUB(Draw_Rule)

    };

}
