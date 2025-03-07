#pragma once

#include <Stuff/Function_Wrapper.h>

#include <Variable_Base.h>
#include <Builder_Stub.h>

#include <Components/Buffer.h>
#include <Components/Graphics_Component_Reconstructor.h>


namespace LR
{

    class Graphics_Component : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component, LV::Variable_Base)

    private:
        Graphics_Component_Reconstructor* m_reconstructor = nullptr;

    protected:
        Buffer m_buffer;

    private:
        LST::Function<void(const Graphics_Component*)> m_on_prepare_func;

    public:
        Graphics_Component();
        ~Graphics_Component();

    public:
        void set_reconstructor(Graphics_Component_Reconstructor* _ptr);

    public:
        inline Buffer& buffer() { return m_buffer; }
        inline const Buffer& buffer() const { return m_buffer; }

        inline Graphics_Component_Reconstructor* reconstructor() { return m_reconstructor; }
        inline const Graphics_Component_Reconstructor* reconstructor() const { return m_reconstructor; }

    public:
        inline void set_on_prepare_func(const LST::Function<void(const Graphics_Component*)>& _func) { m_on_prepare_func = _func; }

    public:
        virtual void update(float _dt) const;
        virtual void prepare_to_draw() const;

        void bind_for_computation() const;

    };



    class Graphics_Component_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component_Stub, LV::Builder_Stub)

        INIT_FIELDS
        ADD_FIELD(unsigned int, attribute_index)
        ADD_FIELD(unsigned int, floats_per_vertex)
        ADD_FIELD(unsigned int, compute_shader_index)
        ADD_FIELD(LDS::Vector<float>, data)
        FIELDS_END

        INIT_CHILDS
        ADD_CHILD("reconstructor_stub", reconstructor_stub)
        CHILDS_END

    public:
        unsigned int attribute_index = 0xFFFFFFFF;
        unsigned int floats_per_vertex = 0;
        unsigned int compute_shader_index = 0xFFFFFFFF;

        LDS::Vector<float> data;

    public:
        Graphics_Component_Reconstructor_Stub* reconstructor_stub = nullptr;

    public:
        ~Graphics_Component_Stub();

    public:
        LST::Function<void(const Graphics_Component*)> on_prepare_func;

    protected:
        INIT_BUILDER_STUB(Graphics_Component)

    };

}
