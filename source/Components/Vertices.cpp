#include <Components/Vertices.h>

using namespace LR;


Vertices::~Vertices()
{

}



void Vertices::init(const float* const _coords, unsigned int _count)
{
    L_ASSERT(_coords != nullptr && _count != 0 && _count % 3 == 0);

	free_memory();
	allocate_memory(_count);
	copy_array(_coords, _count);
}



unsigned int Vertices::vertices_count() const
{
	L_ASSERT(!(m_buffer_size == 0));

	return m_buffer_size / 3;
}
