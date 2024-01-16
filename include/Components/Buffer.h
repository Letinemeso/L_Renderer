#pragma once

#include <glew.h>

#include <L_Debug/L_Debug.h>


namespace LR
{

    class Buffer final
    {
    protected:
        class float_container final
        {
        private:
            friend class Buffer;

        private:
            const unsigned int* buffer = nullptr;
            float* buffer_data = nullptr;
            unsigned int last_requested_index = 0;

        private:
            void M_update_buffer();

        public:
            void operator=(float _f);
            void operator+=(float _f);
            void operator-=(float _f);
            void operator*=(float _f);
            void operator/=(float _f);
            float operator*() const;
            operator float() const;
        };
        float_container fc;

    private:
//        unsigned int m_vertex_array = 0;
        unsigned int m_shader_layout_index = 0xFFFFFFFF;
        unsigned int m_floats_per_vertex = 0;

    protected:
        unsigned int m_buffer = 0;
        float* m_buffer_data = nullptr;
        unsigned int m_buffer_size = 0;

    public:
//        inline void set_vertex_array(unsigned int _value) { m_vertex_array = _value; }

//        inline unsigned int vertex_array() const { return m_vertex_array; }
        inline unsigned int floats_per_vertex() const { return m_floats_per_vertex; }
        inline unsigned int attrib_index() const { return m_shader_layout_index; }

    public:
        Buffer();
        ~Buffer();

        void allocate_memory(unsigned int _size);
        void free_memory();
        void resize(unsigned int _new_size);

        void copy_array(const float* _data, unsigned int _count, unsigned int _offset = 0);
        void use_array(float* _data, unsigned int _count);

        void setup_buffer(unsigned int _attrib_index, unsigned int _floats_per_vertex);

    public:
        float_container& operator[](unsigned int _index);
        float operator[](unsigned int _index) const;

        unsigned int size() const;

        void bind() const;

    };

}
