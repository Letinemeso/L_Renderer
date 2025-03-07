#include <Components/Buffer.h>

using namespace LR;


Buffer::Buffer()
{

}

Buffer::~Buffer()
{
    free_memory();
}



void Buffer::free_memory()
{
    m_buffer_size = 0;
    glDeleteBuffers(1, &m_buffer);
}

void Buffer::resize(unsigned int _new_size)
{
    L_ASSERT(_new_size > 0);

    if(_new_size == m_buffer_size)
        return;

    glDeleteBuffers(1, &m_buffer);
    m_buffer_size = _new_size;

    glGenBuffers(1, &m_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (m_buffer_size + 1), nullptr, GL_DYNAMIC_DRAW);
}


void Buffer::copy_array(const float* _data, unsigned int _count, unsigned int _offset)
{
    L_ASSERT(!(_offset + _count > m_buffer_size || _data == nullptr || _count == 0));

    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * _offset, sizeof(float) * _count, _data);

    if(m_shader_layout_index == 0xFFFFFFFF || m_floats_per_vertex == 0)
        return;

    glVertexAttribPointer(m_shader_layout_index, m_floats_per_vertex, GL_FLOAT, GL_FALSE, sizeof(float) * m_floats_per_vertex, nullptr);
}


void Buffer::setup_buffer(unsigned int _attrib_index, unsigned int _floats_per_vertex)
{
    if(_attrib_index == m_shader_layout_index && m_floats_per_vertex == _floats_per_vertex)
        return;

    if(m_buffer != 0 && m_buffer_size != 0)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
        glVertexAttribPointer(_attrib_index, _floats_per_vertex, GL_FLOAT, GL_FALSE, sizeof(float) * _floats_per_vertex, nullptr);
    }

    glDisableVertexAttribArray(m_shader_layout_index);
    glEnableVertexAttribArray(_attrib_index);

    m_shader_layout_index = _attrib_index;
    m_floats_per_vertex = _floats_per_vertex;
}


void Buffer::modify_buffer(const Element_Modification_Func& _func, unsigned int _offset, unsigned int _amount, unsigned int _stride)
{
    L_ASSERT(_func);
    L_ASSERT(_offset < m_buffer_size);
    L_ASSERT(_stride > 0);

    if(_amount == 0xFFFFFFFF)
        _amount = m_buffer_size - _offset;

    L_ASSERT(_amount > 0);
    L_ASSERT(_offset + _amount <= m_buffer_size);

    bind();

    float* mapped_data = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    L_ASSERT(mapped_data);
    for(unsigned int i = _offset; i < _amount; i += _stride)
        _func(mapped_data[i], i);
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glVertexAttribPointer(m_shader_layout_index, m_floats_per_vertex, GL_FLOAT, GL_FALSE, sizeof(float) * m_floats_per_vertex, nullptr);
}



unsigned int Buffer::size() const
{
    return m_buffer_size;
}



void Buffer::bind() const
{
    L_ASSERT(!(m_buffer == 0 || m_buffer_size == 0));
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void Buffer::bind_to_index(unsigned int _index) const
{
    L_ASSERT(!(m_buffer == 0 || m_buffer_size == 0));

}
