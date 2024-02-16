#include <Window/Window_Controller.h>

using namespace LR;

GLFWwindow* Window_Controller::m_window = nullptr;
Window_Controller::cursor_position Window_Controller::m_prev_cursor_pos;
Window_Controller::window_size Window_Controller::m_window_data;
bool Window_Controller::m_keys_pressed_before[GLFW_KEY_LAST + 1] = { false };
bool Window_Controller::m_mouse_buttons_pressed_before[GLFW_MOUSE_BUTTON_LAST + 1] = { false };
int Window_Controller::m_mouse_wheel_rotation = 0;


void Window_Controller::create_window(unsigned int _width, unsigned int _height, const char* _name)
{
	glfwInit();
	m_window = glfwCreateWindow(_width, _height, _name, 0, 0);
	glfwMakeContextCurrent(m_window);
	glewInit();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetWindowSizeLimits(m_window, _width, _height, _width, _height);

    L_ASSERT(m_window != nullptr);

	m_window_data.width = _width;
	m_window_data.height = _height;

	glfwSetScrollCallback(m_window, [](GLFWwindow*, double /*_x*/, double _y)
	{
		m_mouse_wheel_rotation += (int)_y;
	});
}

void Window_Controller::terminate_window()
{
    glfwTerminate();
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


void Window_Controller::set_cursor_pos(double _x, double _y)
{
	glfwSetCursorPos(m_window, _x, _y);

	m_prev_cursor_pos.x = _x;
    m_prev_cursor_pos.y = _y;
}


Window_Controller::cursor_position Window_Controller::get_cursor_position()
{
    cursor_position result;

    glfwGetCursorPos(m_window, &result.x, &result.y);
    result.y = m_window_data.height - result.y;

    return result;
}

Window_Controller::cursor_position Window_Controller::get_cursor_stride()
{
    cursor_position result = get_cursor_position();

    result.x -= m_prev_cursor_pos.x;
    result.y -= m_prev_cursor_pos.y;

    return result;
}


const Window_Controller::window_size& Window_Controller::get_window_data()
{
	return m_window_data;
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

