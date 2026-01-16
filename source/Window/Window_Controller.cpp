#include <Window/Window_Controller.h>

#include <glew.h>
#include <glfw3.h>

using namespace LR;


Window_Controller::Window_Controller()
{
    LST::Message_Translator::instance().register_message_type<Message__Window_Resized>();

    M_update_cursor_position();
    m_prev_cursor_pos = m_cursor_pos;
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

#ifdef L_DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback([](GLenum _source, GLenum _type, GLuint _id, GLenum _severity, GLsizei _length, const GLchar* _message, const void* _userParam)
    {
        L_LOG(log_level(), "\nOpenGL Error: " + std::string(_message));
    }, nullptr);
#endif

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, _width, _height);

    // glfwSetWindowSizeLimits(m_window, _width, _height, _width, _height);

    L_ASSERT(m_window != nullptr);

    m_window_size.x = _width;
    m_window_size.y = _height;

    glfwSetScrollCallback(m_window, [](GLFWwindow*, double /*_x*/, double _y)
    {
        LR::Window_Controller::instance().instance().register_mouse_wheel_movement((int)_y);
	});

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow*, int _width, int _height)
    {
        LR::Window_Controller::instance().instance().on_window_resized(_width, _height);
    });
}

void Window_Controller::terminate_window()
{
    glfwTerminate();
    m_window = nullptr;
}


void Window_Controller::set_cursor_pos(const glm::vec2& _pos)
{
    glfwSetCursorPos(m_window, _pos.x, _pos.y);

    m_prev_cursor_pos = _pos;
}

void Window_Controller::register_mouse_wheel_movement(int _value)
{
    m_mouse_wheel_rotation += _value;
}

void Window_Controller::on_window_resized(int _new_width, int _new_height)
{
    m_window_size.x = _new_width;
    m_window_size.y = _new_height;

    int fb_x, fb_y;
    glfwGetFramebufferSize(m_window, &fb_x, &fb_y);

    glViewport(0, 0, fb_x, fb_y);

    Message__Window_Resized msg;
    LST::Message_Translator::instance().translate(msg);
}

void Window_Controller::make_fullscreen(bool _fullscreen)
{
    if(_fullscreen)
    {
        if(m_is_fullscreen)
            return;

        m_saved_window_size = m_window_size;
        m_saved_window_position = get_window_position();

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        on_window_resized(mode->width, mode->height);
    }
    else
    {
        if(!m_is_fullscreen)
            return;

        glfwSetWindowMonitor(m_window, nullptr, m_saved_window_position.x, m_saved_window_position.y, m_saved_window_size.x, m_saved_window_size.y, 0);
        on_window_resized(m_saved_window_size.x, m_saved_window_size.y);
    }

    m_is_fullscreen = _fullscreen;
}



void Window_Controller::update()
{
    for (unsigned int i = 0; i <= Keys_Amount; ++i)
		m_keys_pressed_before[i] = glfwGetKey(m_window, i);
    for (unsigned int i = 0; i <= Mouse_Buttons_Amount; ++i)
		m_mouse_buttons_pressed_before[i] = glfwGetMouseButton(m_window, i);

    m_mouse_wheel_rotation = 0;

    m_prev_cursor_pos = m_cursor_pos;
    M_update_cursor_position();

    glfwPollEvents();
}


void Window_Controller::clear(bool _color, bool _depth)
{
    unsigned int mask = 0;
    if(_color)
        mask |= GL_COLOR_BUFFER_BIT;
    if(_depth)
        mask |= GL_DEPTH_BUFFER_BIT;

    L_ASSERT(mask != 0);

    glClear(mask);
}

void Window_Controller::swap_buffers()
{
	glfwSwapBuffers(m_window);
}



void Window_Controller::M_update_cursor_position()
{
    double x, y;
    glfwGetCursorPos(m_window, &x, &y);
    m_cursor_pos.x = x;
    m_cursor_pos.y = m_window_size.y - y;
}



const glm::vec2& Window_Controller::get_cursor_position() const
{
    return m_cursor_pos;
}

glm::vec2 Window_Controller::get_cursor_stride() const
{
    glm::vec2 result = m_cursor_pos;

    result.x -= m_prev_cursor_pos.x;
    result.y -= m_prev_cursor_pos.y;

    return result;
}


const glm::vec2& Window_Controller::get_window_size() const
{
    return m_window_size;
}

float Window_Controller::calculate_window_ratio() const
{
    return m_window_size.x / m_window_size.y;
}


glm::vec2 Window_Controller::get_window_position() const
{
    int window_pos_x, window_pos_y;
    glfwGetWindowPos(m_window, &window_pos_x, &window_pos_y);
    return { window_pos_x, window_pos_y };
}


bool Window_Controller::is_key_down(unsigned int _key) const
{
	return glfwGetKey(m_window, _key) == true;
}

bool Window_Controller::is_mouse_button_down(unsigned int _btn) const
{
	return glfwGetMouseButton(m_window, _btn) == true;
}

bool Window_Controller::key_prev_pressed(unsigned int _key) const
{
	return m_keys_pressed_before[_key];
}

bool Window_Controller::mouse_button_prev_pressed(unsigned int _btn) const
{
	return m_mouse_buttons_pressed_before[_btn];
}

bool Window_Controller::is_mouse_button_up(unsigned int _btn) const
{
    return !Window_Controller::is_mouse_button_down(_btn);
}

bool Window_Controller::mouse_button_was_pressed(unsigned int _btn) const
{
    return Window_Controller::is_mouse_button_down(_btn) && !Window_Controller::mouse_button_prev_pressed(_btn);
}

bool Window_Controller::mouse_button_was_released(unsigned int _btn) const
{
    return !Window_Controller::is_mouse_button_down(_btn) && Window_Controller::mouse_button_prev_pressed(_btn);
}


bool Window_Controller::is_key_up(unsigned int _key) const
{
    return !Window_Controller::is_key_down(_key);
}

bool Window_Controller::key_was_pressed(unsigned int _key) const
{
    return Window_Controller::is_key_down(_key) && !Window_Controller::key_prev_pressed(_key);
}

bool Window_Controller::key_was_released(unsigned int _key) const
{
    return !Window_Controller::is_key_down(_key) && Window_Controller::key_prev_pressed(_key);
}


int Window_Controller::mouse_wheel_rotation() const
{
	return m_mouse_wheel_rotation;
}


void Window_Controller::set_window_should_close(bool _value) const
{
    glfwSetWindowShouldClose(m_window, _value);
}

bool Window_Controller::window_should_close() const
{
    return glfwWindowShouldClose(m_window);
}


void Window_Controller::set_cursor_visibility(bool _visible) const
{
    glfwSetInputMode(m_window, GLFW_CURSOR, _visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

bool Window_Controller::is_cursor_visible() const
{
    return glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL;
}
