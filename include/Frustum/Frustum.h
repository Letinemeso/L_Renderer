#pragma once

#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>


namespace LR
{

    class Frustum
    {
    private:
        glm::vec4 m_planes[6];

    public:
        void recalculate(const glm::mat4x4& _matrix);       //  _matrix is projection * view

    public:
        bool intersects_with_point(const glm::vec3& _point) const;
        bool intersects_with_sphere(const glm::vec3& _center, float _radius) const;
        bool intersects_with_cuboid(const glm::vec3& _center, const glm::vec3& _extents) const;

    };

}
