#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include "vec3.hpp"
#include "mat4x4.hpp"
#include "gtx/transform.hpp"

#include <Camera/Camera_Base.h>

#include <Window/Window_Controller.h>

namespace LR
{

    class Camera_2D : public Camera_Base
	{
	private:
        glm::vec3 m_position;
        float m_view_scale;

    public:
        Camera_2D();
        Camera_2D(const Camera_2D& _other);

	private:
        void M_update_matrix();

	public:
        void set_position(const glm::vec3& _position);
        void set_view_scale(float _scale);

	public:
        inline const glm::vec3& position() const { return m_position; }
        inline float view_scale() const { return m_view_scale; }

        glm::vec3 convert_window_coords(const glm::vec3& _window_coords) const;

	};

}	//LR

#endif // CAMERA_2D_H
