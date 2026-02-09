#pragma once

#include <vec3.hpp>

#include <Data_Structures/Vector.h>

#include <Variable_Base.h>
#include <Builder_Stub.h>

#include <Transformation_Data.h>

#include <Frustum/Frustum.h>


namespace LR
{

    class Border : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Border, LV::Variable_Base)

    private:
        unsigned int m_searched_layout_index = 0xFFFFFFFF;

    public:
        inline void set_searched_layout_index(unsigned int _value) { m_searched_layout_index = _value; }

    public:
        void init(const LV::Variable_Base::Childs_List& _components_list);

        virtual void init(const LDS::Vector<float>& _raw_data) = 0;
        virtual void update(const glm::mat4x4& _transformation) = 0;

    public:
        virtual bool intersects(const Frustum& _frustum) const = 0;

    };


    class Border_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Border_Stub, LV::Builder_Stub)

        INIT_FIELDS
        ADD_FIELD(unsigned int, searched_layout_index)
        FIELDS_END

    public:
        unsigned int searched_layout_index = 0xFFFFFFFF;

    public:
        INIT_NULL_BUILDER_STUB(Border)

        INIT_BUILDER_STUB_SETTERS
        ADD_BUILDER_STUB_SETTER(set_searched_layout_index, searched_layout_index)
        BUILDER_STUB_SETTERS_END

    };

}
