#include <Draw_Modules/Borders/Border__AABB.h>

using namespace LR;


void Border__AABB::init(const LDS::Vector<float>& _raw_data)
{
    m_border.init(_raw_data);
}

void Border__AABB::update(const glm::mat4x4& _transformation)
{
    m_border.update(_transformation);
}



bool Border__AABB::intersects(const Frustum& _frustum) const
{
    return _frustum.intersects_with_cuboid(m_border.center(), m_border.extents());
}
