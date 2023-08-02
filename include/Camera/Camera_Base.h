#ifndef CAMERA_BASE_H
#define CAMERA_BASE_H

#include "../OpenGL/GLM/vec3.hpp"
#include "mat4x4.hpp"
#include "../OpenGL/GLM/gtx/transform.hpp"

#include <Shader/Shader.h>
#include <Event_Controller/Event_Controller.h>

namespace LR
{

    class Camera_Base
    {
    protected:
        glm::mat4x4 m_matrix;

    public:
        inline const glm::mat4x4& matrix() const { return m_matrix; }

    };

}	//LR

#endif // CAMERA_BASE_H
