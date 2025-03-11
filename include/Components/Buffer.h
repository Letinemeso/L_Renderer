#pragma once

#include <glew.h>

#include <L_Debug/L_Debug.h>

#include <Stuff/Function_Wrapper.h>


namespace LR
{

    class Buffer final
    {
    public:
        constexpr static unsigned int All_Elements = 0xFFFFFFFF;

    private:
        unsigned int m_floats_per_vertex = 0;

        unsigned int m_layout_index = 0xFFFFFFFF;
        unsigned int m_binding_point_index = 0xFFFFFFFF;

        unsigned int m_buffer = 0;
        unsigned int m_buffer_size = 0;

    public:
        using Element_Modification_Func = LST::Function<void(float&, unsigned int)>;

    public:
        inline void set_binding_point_index(unsigned int _value) { m_binding_point_index = _value; }

        inline unsigned int floats_per_vertex() const { return m_floats_per_vertex; }
        inline unsigned int layout_index() const { return m_layout_index; }
        inline unsigned int binding_point_index() const { return m_binding_point_index; }

    public:
        Buffer();
        ~Buffer();

        void free_memory();
        void resize(unsigned int _new_size);
        void copy_array(const float* _data, unsigned int _count, unsigned int _offset = 0);

        void set_layout_index(unsigned int _index);
        void set_floats_per_vertex(unsigned int _floats_per_vertex);

        void modify_buffer(const Element_Modification_Func& _func, unsigned int _offset = 0, unsigned int _amount = All_Elements, unsigned int _stride = 1);

    public:
        unsigned int size() const;

        void bind_to_layout() const;
        void bind_to_binding_point() const;

    };

}
