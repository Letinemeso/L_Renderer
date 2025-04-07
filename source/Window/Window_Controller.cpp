#include <Window/Window_Controller.h>

#include <glew.h>
#include <glfw3.h>

using namespace LR;


Window_Controller::Window_Controller()
{

}

Window_Controller::~Window_Controller()
{
    if(m_window)
        terminate_window();
}



void Window_Controller::create_window(unsigned int _width, unsigned int _height, const char* _name)
{
    L_ASSERT(m_window == nullptr);

	glfwInit();
	m_window = glfwCreateWindow(_width, _height, _name, 0, 0);
	glfwMakeContextCurrent(m_window);
	glewInit();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetWindowSizeLimits(m_window, _width, _height, _width, _height);

    L_ASSERT(m_window != nullptr);

    m_window_size.x = _width;
    m_window_size.y = _height;

    glfwSetScrollCallback(m_window, [](GLFWwindow*, double /*_x*/, double _y)
    {
        LR::Window_Controller::instance().instance().register_mouse_wheel_movement((int)_y);
	});
}

void Window_Controller::terminate_window()
{
    glfwTerminate();
    m_window = nullptr;
}


void Window_Controller::set_cursor_pos(double _x, double _y)
{
    glfwSetCursorPos(m_window, _x, _y);

    m_prev_cursor_pos.x = _x;
    m_prev_cursor_pos.y = _y;
}

void Window_Controller::register_mouse_wheel_movement(int _value)
{
    m_mouse_wheel_rotation += _value;
}



void Window_Controller::update()
{
	for (unsigned int i = 0; i <= GLFW_KEY_LAST; ++i)
		m_keys_pressed_before[i] = glfwGetKey(m_window, i);
	for (unsigned int i = 0; i <= GLFW_MOUSE_BUTTON_LAST; ++i)
		m_mouse_buttons_pressed_before[i] = glfwGetMouseButton(m_window, i);

	m_mouse_wheel_rotation = 0;

	glfwPollEvents();

    m_prev_cursor_pos = get_cursor_position();
}



bool Window_Controller::window_should_close()
{
	return glfwWindowShouldClose(m_window);
}

void Window_Controller::swap_buffers()
{
	glfwSwapBuffers(m_window);
}



glm::vec2 Window_Controller::get_cursor_position()
{
    double x, y;
    glfwGetCursorPos(m_window, &x, &y);

    glm::vec2 result;
    result.x = x;
    result.y = m_window_size.y - (float)y;

    return result;
}

glm::vec2 Window_Controller::get_cursor_stride()
{
    glm::vec2 result = get_cursor_position();

    result.x -= m_prev_cursor_pos.x;
    result.y -= m_prev_cursor_pos.y;

    return result;
}


const glm::vec2& Window_Controller::get_window_size()
{
    return m_window_size;
}

float Window_Controller::calculate_window_ratio()
{
    return m_window_size.x / m_window_size.y;
}


bool Window_Controller::is_key_down(unsigned int _key)
{
	return glfwGetKey(m_window, _key) == true;
}

bool Window_Controller::is_mouse_button_down(unsigned int _btn)
{
	return glfwGetMouseButton(m_window, _btn) == true;
}

bool Window_Controller::key_prev_pressed(unsigned int _key)
{
	return m_keys_pressed_before[_key];
}

bool Window_Controller::mouse_button_prev_pressed(unsigned int _btn)
{
	return m_mouse_buttons_pressed_before[_btn];
}

bool Window_Controller::is_mouse_button_up(unsigned int _btn)
{
    return !Window_Controller::is_mouse_button_down(_btn);
}

bool Window_Controller::mouse_button_was_pressed(unsigned int _btn)
{
    return Window_Controller::is_mouse_button_down(_btn) && !Window_Controller::mouse_button_prev_pressed(_btn);
}

bool Window_Controller::mouse_button_was_released(unsigned int _btn)
{
    return !Window_Controller::is_mouse_button_down(_btn) && Window_Controller::mouse_button_prev_pressed(_btn);
}


bool Window_Controller::is_key_up(unsigned int _key)
{
    return !Window_Controller::is_key_down(_key);
}

bool Window_Controller::key_was_pressed(unsigned int _key)
{
    return Window_Controller::is_key_down(_key) && !Window_Controller::key_prev_pressed(_key);
}

bool Window_Controller::key_was_released(unsigned int _key)
{
    return !Window_Controller::is_key_down(_key) && Window_Controller::key_prev_pressed(_key);
}


int Window_Controller::mouse_wheel_rotation()
{
	return m_mouse_wheel_rotation;
}

