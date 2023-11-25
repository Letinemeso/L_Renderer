#ifndef CAMERA_BASE_H
#define CAMERA_BASE_H

#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtx/transform.hpp>

namespace LR
{

    class Camera_Base
    {
    protected:
        glm::mat4x4 m_matrix;

    public:
        Camera_Base();
        virtual ~Camera_Base();

    public:
        inline const glm::mat4x4& matrix() const { return m_matrix; }

    };

}	//LR

#endif // CAMERA_BASE_H
