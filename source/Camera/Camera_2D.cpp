#include <Camera/Camera_2D.h>

using namespace LR;


Camera_2D::Camera_2D()
{

}

Camera_2D::Camera_2D(const Camera_2D& _other)
{
    m_position = _other.m_position;
    m_view_scale = _other.m_view_scale;
    m_matrix = _other.m_matrix;
}



void Camera_2D::M_update_matrix()
{
    const glm::vec2& draw_area_size = m_draw_area_size_getter ? m_draw_area_size_getter() : LR::Window_Controller::instance().get_window_size();
    glm::vec2 diff = draw_area_size * 0.5f * m_view_scale;

	m_matrix = glm::ortho(
        -diff.x + m_position.x, diff.x + m_position.x,
        -diff.y + m_position.y, diff.y + m_position.y,
		-1.0f, 1.0f
	);
}



void Camera_2D::set_position(const glm::vec2& _position)
{
	m_position = _position;
	M_update_matrix();
}

void Camera_2D::set_view_scale(float _scale)
{
	if(_scale < 0.0f)
		m_view_scale = 0.1f;
	else
		m_view_scale = _scale;
	M_update_matrix();
}



glm::vec3 Camera_2D::convert_window_coords(const glm::vec2& _window_coords) const
{
    Window_Controller& window_controller = Window_Controller::instance();

    glm::vec2 screen_center = window_controller.get_window_size() * 0.5f;
    glm::vec2 offset_from_center = _window_coords - screen_center;
    offset_from_center *= m_view_scale;

    glm::vec3 result = { m_position + offset_from_center, 0.0f };

	return result;
}

glm::vec3 Camera_2D::convert_window_coords(const glm::vec2& _window_coords, const glm::vec2& _draw_area_size) const
{
    Window_Controller& window_controller = Window_Controller::instance();

    glm::vec2 screen_center = window_controller.get_window_size() * 0.5f;
    glm::vec2 offset_from_center = _window_coords - screen_center;

    glm::vec2 window_to_area_size_ratio = _draw_area_size / window_controller.get_window_size();
    offset_from_center *= window_to_area_size_ratio;

    offset_from_center *= m_view_scale;

    glm::vec3 result = { m_position + offset_from_center, 0.0f };

    return result;
}
