#ifndef __BUFFER
#define __BUFFER

#include <glew.h>

#include <L_Debug/L_Debug.h>


namespace LR
{

    class Buffer
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
        const unsigned int* m_vertex_array = nullptr;
        unsigned int m_shader_layout_index = 0xFFFFFFFF;
        unsigned int m_floats_per_vertex = 0;

    protected:
        unsigned int m_buffer = 0;
        float* m_buffer_data = nullptr;
        unsigned int m_buffer_size = 0;

    public:
        inline void set_vertex_array(const unsigned int* _ptr) { m_vertex_array = _ptr; }
        inline void set_floats_per_vertex(unsigned int _value) { m_floats_per_vertex = _value; }

    public:
        Buffer();
        virtual ~Buffer();

        virtual void allocate_memory(unsigned int _size);
        virtual void free_memory();
        virtual void resize(unsigned int _new_size);

        virtual void copy_array(const float* _data, unsigned int _count, unsigned int _offset = 0);

        virtual void setup_buffer(unsigned int _attrib_index);

    public:
        float_container& operator[](unsigned int _index);
        float operator[](unsigned int _index) const;

        unsigned int size() const;

        void bind() const;

    };


}   /*LR*/

#endif
