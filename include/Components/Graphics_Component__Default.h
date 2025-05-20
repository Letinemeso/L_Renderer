#pragma once

#include <Stuff/Function_Wrapper.h>

#include <Variable_Base.h>
#include <Builder_Stub.h>

#include <Components/Buffer.h>
#include <Components/Graphics_Component_Reconstructor.h>
#include <Components/Graphics_Component.h>


namespace LR
{

    class Graphics_Component__Default : public Graphics_Component
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component__Default, LR::Graphics_Component)

    private:
        Graphics_Component_Reconstructor* m_reconstructor = nullptr;

    protected:
        Buffer m_buffer;

    public:
        Graphics_Component__Default();
        ~Graphics_Component__Default();

    public:
        void set_reconstructor(Graphics_Component_Reconstructor* _ptr);

    public:
        inline Buffer& buffer() { return m_buffer; }
        inline const Buffer& buffer() const { return m_buffer; }

        inline Graphics_Component_Reconstructor* reconstructor() { return m_reconstructor; }
        inline const Graphics_Component_Reconstructor* reconstructor() const { return m_reconstructor; }

    public:
        void update(float _dt) override;
        void prepare_to_draw() const override;

        void bind_for_computation() const;

    };



    class Graphics_Component_Stub__Default : public LR::Graphics_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component_Stub__Default, LR::Graphics_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(unsigned int, floats_per_vertex)
        ADD_FIELD(unsigned int, layout_index)
        ADD_FIELD(unsigned int, binding_point_index)
        ADD_FIELD(LDS::Vector<float>, data)
        FIELDS_END

        INIT_CHILDS
        ADD_CHILD("reconstructor_stub", reconstructor_stub)
        CHILDS_END

    public:
        unsigned int floats_per_vertex = 0;
        unsigned int layout_index = 0xFFFFFFFF;
        unsigned int binding_point_index = 0xFFFFFFFF;

        LDS::Vector<float> data;

    public:
        Graphics_Component_Reconstructor_Stub* reconstructor_stub = nullptr;

    public:
        ~Graphics_Component_Stub__Default();

    protected:
        INIT_BUILDER_STUB(Graphics_Component__Default)

    };

}
