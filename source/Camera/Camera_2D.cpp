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
    glm::vec2 diff = LR::Window_Controller::instance().get_window_size() * 0.5f * m_view_scale;

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
    glm::vec3 result;

    glm::vec2 ratio = _window_coords / LR::Window_Controller::instance().get_window_size();

    glm::vec2 left_bottom_edge = (-LR::Window_Controller::instance().get_window_size() * 0.5f * m_view_scale) + m_position;
    glm::vec2 view = LR::Window_Controller::instance().get_window_size() * m_view_scale;

    result.x = view.x * ratio.x + left_bottom_edge.x;
    result.y = view.y * ratio.y + left_bottom_edge.y;
    result.z = 0.0f;

	return result;
}
