#pragma once

#include <Stuff/Function_Wrapper.h>

#include <Variable_Base.h>
#include <Builder_Stub.h>

#include <Components/Buffer.h>


namespace LR
{

    class Graphics_Component : public LV::Variable_Base
    {
    public:
        DECLARE_VARIABLE;

    protected:
        Buffer m_buffer;

    private:
        LST::Function<void(const Graphics_Component*)> m_on_prepare_func;

    public:
        Graphics_Component();
        ~Graphics_Component();

    public:
        inline Buffer& buffer() { return m_buffer; }
        inline const Buffer& buffer() const { return m_buffer; }

    public:
        inline void set_on_prepare_func(const LST::Function<void(const Graphics_Component*)>& _func) { m_on_prepare_func = _func; }

    public:
        virtual void prepare() const;

    };



    class Graphics_Component_Stub : public LV::Builder_Stub
    {
    public:
        DECLARE_VARIABLE;

    public:
        unsigned int attribute_index = 0;
        unsigned int floats_per_vertex = 0;

        float* data = nullptr;
        unsigned int data_size = 0;

    public:
        LST::Function<void(const Graphics_Component*)> on_prepare_func;

    protected:
        LV::Variable_Base* M_construct_product() const override;
        void M_init_constructed_product(LV::Variable_Base* _product) const override;

    };

}
