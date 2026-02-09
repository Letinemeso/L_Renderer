#pragma once

#include <Draw_Modules/Borders/Border.h>


namespace LR
{

    class Border__AABB : public Border
    {
    public:
        INIT_VARIABLE(LR::Border__AABB, LR::Border)

    private:
        glm::vec3 m_local_center;
        glm::vec3 m_local_extents;

        glm::vec3 m_global_center;
        glm::vec3 m_global_extents;

    public:
        void init(const LDS::Vector<float>& _raw_data) override;
        void update(const glm::mat4x4& _transformation) override;

    public:
        bool intersects(const Frustum& _frustum) const override;

    };


    class Border_Stub__AABB : public Border_Stub
    {
    public:
        INIT_VARIABLE(LR::Border_Stub__AABB, LR::Border_Stub)

    public:
        INIT_DEFAULT_BUILDER_STUB(Border__AABB)

    };

}
