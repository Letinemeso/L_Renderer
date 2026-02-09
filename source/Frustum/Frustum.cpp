#include <Frustum/Frustum.h>

#include <Stuff/Math_Stuff.h>

using namespace LR;


void Frustum::recalculate(const glm::mat4x4& _matrix)
{
    glm::mat4x4 transposed_matrix = glm::transpose(_matrix);

    m_planes[0] = transposed_matrix[3] + transposed_matrix[0];
    m_planes[1] = transposed_matrix[3] - transposed_matrix[0];
    m_planes[2] = transposed_matrix[3] + transposed_matrix[1];
    m_planes[3] = transposed_matrix[3] - transposed_matrix[1];
    m_planes[4] = transposed_matrix[3] + transposed_matrix[2];
    m_planes[5] = transposed_matrix[3] - transposed_matrix[2];

    for(unsigned int i = 0; i < 6; ++i)
    {
        glm::vec4& plane = m_planes[i];

        float length = LST::Math::vector_length(glm::vec3(plane));
        plane /= length;
    }
}



bool Frustum::intersects_with_point(const glm::vec3& _point) const
{
    for(unsigned int p_i = 0; p_i < 6; ++p_i)
    {
        const glm::vec4& plane = m_planes[p_i];

        float signed_distance = plane.x * _point.x + plane.y * _point.y + plane.z * _point.z + plane.w;

        if(signed_distance < 0.0f)
            return false;
    }

    return true;
}

bool Frustum::intersects_with_sphere(const glm::vec3& _center, float _radius) const
{
    for(unsigned int p_i = 0; p_i < 6; ++p_i)
    {
        const glm::vec4& plane = m_planes[p_i];

        float signed_distance = plane.x * _center.x + plane.y * _center.y + plane.z * _center.z + plane.w;

        if(signed_distance < -_radius)
            return false;
    }

    return true;
}

bool Frustum::intersects_with_cuboid(const glm::vec3& _center, const glm::vec3& _extents) const
{
    for(unsigned int p_i = 0; p_i < 6; ++p_i)
    {
        const glm::vec4& plane = m_planes[p_i];

        float signed_distance = plane.x * _center.x + plane.y * _center.y + plane.z * _center.z + plane.w;

        float max_stride = 0.0f;
        for(unsigned int i = 0; i < 3; ++i)
            max_stride += _extents[i] * fabsf(plane[i]);

        float eps = max_stride * 1e-3f;

        if(signed_distance < -max_stride - eps)
            return false;
    }

    return true;
}
