#include <Draw_Modules/Borders/Border__AABB.h>

using namespace LR;


void Border__AABB::init(const LDS::Vector<float>& _raw_data)
{
    if(_raw_data.size() == 0)
        return;

    glm::vec3 min, max;
    for(unsigned int i = 0; i < 3; ++i)
    {
        min[i] = std::numeric_limits<float>::max();
        max[i] = std::numeric_limits<float>::lowest();
    }

    for(unsigned int i = 0; i < _raw_data.size(); ++i)
    {
        unsigned int index = i % 3;
        float value = _raw_data[i];

        if(value > max[index])
            max[index] = value;
        if(value < min[index])
            min[index] = value;
    }

    m_local_center = (min + max) * 0.5f;
    m_local_extents = (max - min) * 0.5f;
}

void Border__AABB::update(const glm::mat4x4& _transformation)
{
    m_global_center = _transformation * glm::vec4(m_local_center, 1.0f);

    glm::mat3x3 transformation_without_movement = _transformation;
    m_global_extents = {0.0f, 0.0f, 0.0f};
    for(unsigned int i = 0; i < 3; ++i)
        m_global_extents += glm::abs(transformation_without_movement[i]) * m_local_extents[i];
}



bool Border__AABB::intersects(const Frustum& _frustum) const
{
    return _frustum.intersects_with_cuboid(m_global_center, m_global_extents);
}
