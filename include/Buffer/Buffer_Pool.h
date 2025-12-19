#pragma once

#include <Data_Structures/List.h>
#include <Data_Structures/AVL_Tree.h>


namespace LR
{

    class Buffer_Pool
    {
    private:
        using Buffer_Ids_List = LDS::List<unsigned int>;
        using Buffer_Ids_Tree = LDS::AVL_Tree<unsigned int>;

        Buffer_Ids_List m_free_buffers;
        Buffer_Ids_Tree m_reserved_buffers;

        unsigned int m_max_buffers = 10000;

    private:
        Buffer_Pool() {  }
        Buffer_Pool(const Buffer_Pool&) = delete;
        Buffer_Pool(Buffer_Pool&&) = delete;
        void operator=(const Buffer_Pool&) = delete;
        void operator=(Buffer_Pool&&) = delete;

    public:
        ~Buffer_Pool();

    private:
        void M_allocate_additional_buffers();

    public:
        inline static Buffer_Pool& instance() { static Buffer_Pool s_instance; return s_instance; }

        inline unsigned int free_buffers_amount() const { return m_free_buffers.size(); }
        inline unsigned int reserved_buffers_amount() const { return m_reserved_buffers.size(); }
        inline unsigned int buffers_amount() const { return m_free_buffers.size() + m_reserved_buffers.size(); }

        inline void set_max_buffers(unsigned int _value) { m_max_buffers = _value; }

    public:
        unsigned int reserve();
        void free(unsigned int _buffer);

    };

}
