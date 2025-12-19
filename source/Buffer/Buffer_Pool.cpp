#include <Buffer/Buffer_Pool.h>

#include <Data_Structures/Vector.h>

#include <glew.h>

using namespace LR;

namespace LR
{

    constexpr unsigned int Generated_Buffers_Per_Request = 500;

}


Buffer_Pool::~Buffer_Pool()
{
    unsigned int amount = buffers_amount();

    LDS::Vector<unsigned int> buffers(amount);

    for(Buffer_Ids_List::Iterator it = m_free_buffers.begin(); !it.end_reached(); ++it)
        buffers.push(*it);
    for(Buffer_Ids_Tree::Iterator it = m_reserved_buffers.iterator(); !it.end_reached(); ++it)
        buffers.push(*it);

    glDeleteBuffers(amount, buffers.raw_data());
}



void Buffer_Pool::M_allocate_additional_buffers()
{
    unsigned int amount = buffers_amount();

    L_ASSERT(amount <= m_max_buffers);

    unsigned int requested_buffers_amount = Generated_Buffers_Per_Request;
    if(amount + requested_buffers_amount > m_max_buffers)
        requested_buffers_amount = m_max_buffers - amount + 1;

    LDS::Vector<unsigned int> buffers(requested_buffers_amount, 0);
    glGenBuffers(requested_buffers_amount, buffers.raw_data());

    for(unsigned int i = 0; i < buffers.size(); ++i)
        m_free_buffers.push_back(buffers[i]);

    std::cout << buffers_amount() << std::endl;
}



unsigned int Buffer_Pool::reserve()
{
    if(m_free_buffers.size() == 0)
        M_allocate_additional_buffers();

    unsigned int result = m_free_buffers.front();
    m_free_buffers.pop_front();
    m_reserved_buffers.insert(result);

    return result;
}

void Buffer_Pool::free(unsigned int _buffer)
{
    L_ASSERT(!m_free_buffers.find(_buffer).is_ok());

    Buffer_Ids_Tree::Iterator it = m_reserved_buffers.find(_buffer);
    L_ASSERT(it.is_ok());

    unsigned int buffer = *it;
    m_reserved_buffers.erase(it);
    m_free_buffers.push_front(buffer);
}
