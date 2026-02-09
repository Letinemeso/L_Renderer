#pragma once

#include <Stuff/Function_Wrapper.h>

#include <Variable_Base.h>
#include <Builder_Stub.h>

#include <Data_Provider.h>

#include <Buffer/Buffer.h>
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

        unsigned int m_required_compute_shader_invocations = 0;

    public:
        Graphics_Component__Default();
        ~Graphics_Component__Default();

    public:
        inline void set_required_compute_shader_invocations(unsigned int _value) { m_required_compute_shader_invocations = _value; }

        void set_reconstructor(Graphics_Component_Reconstructor* _ptr);

    public:
        inline Buffer& buffer() { return m_buffer; }
        inline const Buffer& buffer() const { return m_buffer; }

        inline Graphics_Component_Reconstructor* reconstructor() { return m_reconstructor; }
        inline const Graphics_Component_Reconstructor* reconstructor() const { return m_reconstructor; }

    protected:
        void M_on_parent_draw_module_set() override;

    public:
        unsigned int layout_index() const override;
        unsigned int vertices_amount() const override;
        unsigned int required_compute_shader_invocations() const override;
        void setup_buffer() const override;
        void update(float _dt) override;
        void prepare_to_draw() const override;
        void bind_for_computation() const override;

    };



    class Graphics_Component_Stub__Default : public LR::Graphics_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component_Stub__Default, LR::Graphics_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(unsigned int, floats_per_vertex)
        ADD_FIELD(unsigned int, layout_index)
        ADD_FIELD(unsigned int, binding_point_index)
        ADD_FIELD(unsigned int, required_compute_shader_invocations)
        ADD_FIELD(bool, enable_instancing)
        ADD_FIELD(LDS::Vector<float>, data)
        FIELDS_END

        INIT_CHILDS
        ADD_CHILD("reconstructor_stub", reconstructor_stub)
        ADD_CHILD("data_provider", data_provider)
        CHILDS_END

    public:
        unsigned int floats_per_vertex = 0;
        unsigned int layout_index = 0xFFFFFFFF;
        unsigned int binding_point_index = 0xFFFFFFFF;
        unsigned int required_compute_shader_invocations = 0;

        bool enable_instancing = false;

        LDS::Vector<float> data;

    public:
        Graphics_Component_Reconstructor_Stub* reconstructor_stub = nullptr;
        LEti::Data_Provider* data_provider = nullptr;

    public:
        ~Graphics_Component_Stub__Default();

    public:
        const LDS::Vector<float>& select_data() const;

    protected:
        INIT_BUILDER_STUB(Graphics_Component__Default)

    };

}
