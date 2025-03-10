#pragma once

#include <glew.h>

#include <L_Debug/L_Debug.h>

#include <Stuff/Function_Wrapper.h>


namespace LR
{

    class Buffer final
    {
    private:
        unsigned int m_shader_layout_index = 0xFFFFFFFF;
        unsigned int m_floats_per_vertex = 0;

        unsigned int m_compute_shader_index = 0xFFFFFFFF;

        unsigned int m_buffer = 0;
        unsigned int m_buffer_size = 0;

    public:
        using Element_Modification_Func = LST::Function<void(float&, unsigned int)>;

    public:
        inline void set_compute_shader_index(unsigned int _value) { m_compute_shader_index = _value; }

        inline unsigned int floats_per_vertex() const { return m_floats_per_vertex; }
        inline unsigned int attrib_index() const { return m_shader_layout_index; }

    public:
        Buffer();
        ~Buffer();

        void free_memory();
        void resize(unsigned int _new_size);
        void copy_array(const float* _data, unsigned int _count, unsigned int _offset = 0);

        void set_shader_layout_index(unsigned int _index);
        void set_floats_per_vertex(unsigned int _floats_per_vertex);

        void modify_buffer(const Element_Modification_Func& _func, unsigned int _offset = 0, unsigned int _amount = 0xFFFFFFFF, unsigned int _stride = 1);

    public:
        unsigned int size() const;

        void bind_for_draw() const;
        void bind_for_computation() const;

    };

}
