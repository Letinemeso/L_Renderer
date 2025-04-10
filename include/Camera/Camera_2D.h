#pragma once

#include <vec2.hpp>

#include <Stuff/Function_Wrapper.h>

#include <Camera/Camera_Base.h>
#include <Window/Window_Controller.h>

namespace LR
{

    class Camera_2D : public Camera_Base
	{
	private:
        glm::vec2 m_position = { 0.0f, 0.0f };
        float m_view_scale = 1.0f;

        LST::Function<const glm::vec2&()> m_draw_area_size_getter;

    public:
        Camera_2D();
        Camera_2D(const Camera_2D& _other);

	private:
        void M_update_matrix();

	public:
        inline void set_draw_area_size_getter(const LST::Function<const glm::vec2&()>& _func) { m_draw_area_size_getter = _func; }

        void set_position(const glm::vec2& _position);
        void set_view_scale(float _scale);

	public:
        inline const glm::vec2& position() const { return m_position; }
        inline float view_scale() const { return m_view_scale; }

        glm::vec3 convert_window_coords(const glm::vec2& _window_coords) const;

	};

}	//LR
