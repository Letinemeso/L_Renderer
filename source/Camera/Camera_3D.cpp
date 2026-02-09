#include <Camera/Camera_3D.h>

using namespace LR;


Camera_3D::Camera_3D()
{

}

Camera_3D::Camera_3D(const Camera_3D& _other)
{
    m_settings = _other.m_settings;
}



void Camera_3D::reconfigure()
{
    LST::Math::shrink_vector_to_1(m_settings.direction);
    LST::Math::shrink_vector_to_1(m_settings.top);

    float window_ratio = LR::Window_Controller::instance().calculate_window_ratio();

    glm::mat4x4 perspective_matrix = glm::perspective<float>(m_settings.field_of_view, window_ratio, m_settings.min_distance, m_settings.max_distance);
    glm::mat4x4 look_direction_matrix = glm::lookAt(m_settings.position, m_settings.direction + m_settings.position, m_settings.top);

    m_matrix = perspective_matrix * look_direction_matrix;

    m_frustum.recalculate(m_matrix);
}


void Camera_3D::set_settings(const Settings& _settings)
{
    m_settings = _settings;
    reconfigure();
}
