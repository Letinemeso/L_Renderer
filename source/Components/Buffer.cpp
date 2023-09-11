#include <Components/Buffer.h>

using namespace LR;


void Buffer::float_container::M_update_buffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, *buffer);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * last_requested_index, sizeof(float), &buffer_data[last_requested_index]);
}



void Buffer::float_container::operator=(float _f)
{
    buffer_data[last_requested_index] = _f;
    M_update_buffer();
}

void Buffer::float_container::operator+=(float _f)
{
    buffer_data[last_requested_index] += _f;
    M_update_buffer();
}

void Buffer::float_container::operator-=(float _f)
{
    buffer_data[last_requested_index] -= _f;
    M_update_buffer();
}

void Buffer::float_container::operator*=(float _f)
{
    buffer_data[last_requested_index] *= _f;
    M_update_buffer();
}

void Buffer::float_container::operator/=(float _f)
{
    buffer_data[last_requested_index] /= _f;
    M_update_buffer();
}

float Buffer::float_container::operator*() const
{
    return buffer_data[last_requested_index];
}

Buffer::float_container::operator float() const
{
    return buffer_data[last_requested_index];
}



Buffer::Buffer()
{
    fc.buffer = &m_buffer;
}

Buffer::~Buffer()
{
    free_memory();
}



void Buffer::allocate_memory(unsigned int _size)
{
    L_ASSERT(!(_size == 0 || m_vertex_array == nullptr));

    free_memory();

    m_buffer_data = new float[_size];
    fc.buffer_data = m_buffer_data;
    for (unsigned int i = 0; i < _size; ++i)
        m_buffer_data[i] = 0.0f;
    m_buffer_size = _size;

    glBindVertexArray(*m_vertex_array);

    glGenBuffers(1, &m_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (m_buffer_size + 1), nullptr, GL_DYNAMIC_DRAW);
}

void Buffer::free_memory()
{
    delete[] m_buffer_data;
    m_buffer_data = nullptr;
    fc.buffer_data = nullptr;
    m_buffer_size = 0;

    glDeleteBuffers(1, &m_buffer);
}

void Buffer::resize(unsigned int _new_size)
{
    L_ASSERT(!(_new_size == 0 || m_vertex_array == nullptr));
    glBindVertexArray(*m_vertex_array);

    float* tempf = new float[_new_size];
    if (m_buffer_size < _new_size)
    {
        for (unsigned int i = 0; i < m_buffer_size; ++i)
            tempf[i] = m_buffer_data[i];
        for (unsigned int i = m_buffer_size; i < _new_size; ++i)
            tempf[i] = 0.0f;
    }
    else
    {
        for (unsigned int i = 0; i < _new_size; ++i)
            tempf[i] = m_buffer_data[i];
    }

    glDeleteBuffers(1, &m_buffer);
    delete[] m_buffer_data;

    m_buffer_size = _new_size;
    m_buffer_data = tempf;
    fc.buffer_data = tempf;
    glGenBuffers(1, &m_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (m_buffer_size + 1), m_buffer_data, GL_DYNAMIC_DRAW);
}


void Buffer::copy_array(const float* _data, unsigned int _count, unsigned int _offset)
{
    L_ASSERT(!(_offset + _count > m_buffer_size || _data == nullptr || _count == 0 || m_vertex_array == nullptr));

    for(unsigned int i=0; i<_count; ++i)
        m_buffer_data[i + _offset] = _data[i];

    glBindVertexArray(*m_vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * _offset, sizeof(float) * _count, _data);

    if(m_shader_layout_index == 0xFFFFFFFF || m_floats_per_vertex == 0)
        return;

    glVertexAttribPointer(m_shader_layout_index, m_floats_per_vertex, GL_FLOAT, GL_FALSE, sizeof(float) * m_floats_per_vertex, nullptr);
}


void Buffer::setup_buffer(unsigned int _attrib_index)
{
    L_ASSERT(m_buffer != 0 && m_buffer_size != 0 && m_buffer_data != nullptr && m_vertex_array != nullptr);

    if(_attrib_index == m_shader_layout_index)
        return;

    glBindVertexArray(*m_vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glVertexAttribPointer(_attrib_index, m_floats_per_vertex, GL_FLOAT, GL_FALSE, sizeof(float) * m_floats_per_vertex, nullptr);

    glDisableVertexAttribArray(m_shader_layout_index);
    glEnableVertexAttribArray(_attrib_index);

    m_shader_layout_index = _attrib_index;
}



Buffer::float_container& Buffer::operator[](unsigned int _index)
{
    L_ASSERT(!(_index >= m_buffer_size));
    fc.last_requested_index = _index;
    return fc;
}

float Buffer::operator[](unsigned int _index) const
{
    L_ASSERT(!(_index >= m_buffer_size));
    return m_buffer_data[_index];
}



unsigned int Buffer::size() const
{
    return m_buffer_size;
}



void Buffer::bind() const
{
    L_ASSERT(!(m_buffer == 0 || m_buffer_size == 0 || m_buffer_data == nullptr || m_vertex_array == nullptr));
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}
