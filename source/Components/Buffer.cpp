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
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * m_buffer_size, nullptr, GL_DYNAMIC_DRAW);
}


void Buffer::copy_array(const float* _data, unsigned int _count, unsigned int _offset)
{
    L_ASSERT(!(_offset + _count > m_buffer_size || _data == nullptr || _count == 0));

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_buffer);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * _offset, sizeof(float) * _count, _data);

    if(m_shader_layout_index == 0xFFFFFFFF || m_floats_per_vertex == 0)
        return;

    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glVertexAttribPointer(m_shader_layout_index, m_floats_per_vertex, GL_FLOAT, GL_FALSE, sizeof(float) * m_floats_per_vertex, nullptr);
}


void Buffer::set_shader_layout_index(unsigned int _index)
{
    L_ASSERT(_index != 0xFFFFFFFF);

    if(_index == m_shader_layout_index)
        return;

    glDisableVertexAttribArray(m_shader_layout_index);
    glEnableVertexAttribArray(_index);

    m_shader_layout_index = _index;

    if(m_buffer == 0 || m_buffer_size == 0 || m_floats_per_vertex == 0)
        return;

    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glVertexAttribPointer(m_shader_layout_index, m_floats_per_vertex, GL_FLOAT, GL_FALSE, sizeof(float) * m_floats_per_vertex, nullptr);
}

void Buffer::set_floats_per_vertex(unsigned int _floats_per_vertex)
{
    L_ASSERT(_floats_per_vertex > 0);

    if(_floats_per_vertex == m_floats_per_vertex)
        return;

    m_floats_per_vertex = _floats_per_vertex;

    if(m_buffer == 0 || m_buffer_size == 0 || m_shader_layout_index == 0xFFFFFFFF)
        return;

    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glVertexAttribPointer(m_shader_layout_index, m_floats_per_vertex, GL_FLOAT, GL_FALSE, sizeof(float) * m_floats_per_vertex, nullptr);
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

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_buffer);

    float* mapped_data = (float*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
    L_ASSERT(mapped_data);
    for(unsigned int i = _offset; i < _offset + _amount; i += _stride)
        _func(mapped_data[i], i);
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glVertexAttribPointer(m_shader_layout_index, m_floats_per_vertex, GL_FLOAT, GL_FALSE, sizeof(float) * m_floats_per_vertex, nullptr);
}



unsigned int Buffer::size() const
{
    return m_buffer_size;
}



void Buffer::bind_for_draw() const
{
    L_ASSERT(!(m_buffer == 0 || m_buffer_size == 0));

    if(m_shader_layout_index == 0xFFFFFFFF)
        return;

    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void Buffer::bind_for_computation() const
{
    L_ASSERT(!(m_buffer == 0 || m_buffer_size == 0));

    if(m_compute_shader_index == 0xFFFFFFFF)
        return;

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_compute_shader_index, m_buffer);
}
