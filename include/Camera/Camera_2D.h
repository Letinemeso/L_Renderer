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
        glm::vec2 m_position{ 0.0f, 0.0f };
        float m_view_scale = 1.0f;

    public:
        Camera_2D();
        Camera_2D(const Camera_2D& _other);

	private:
        void M_update_matrix();

	public:
        void set_position(const glm::vec2& _position);
        void set_view_scale(float _scale);

	public:
        inline const glm::vec2& position() const { return m_position; }
        inline float view_scale() const { return m_view_scale; }

        glm::vec3 convert_window_coords(const glm::vec2& _window_coords) const;

	};

}	//LR

#endif // CAMERA_2D_H
