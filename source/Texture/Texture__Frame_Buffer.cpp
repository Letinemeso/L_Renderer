#include <Texture/Texture__Frame_Buffer.h>

#include <glew.h>

#include <Binds_Controller/Binds_Controller.h>

using namespace LR;


Texture__Frame_Buffer::Texture__Frame_Buffer() : Texture(), m_clear_hint(GL_COLOR_BUFFER_BIT)
{
    glGenFramebuffers(1, &m_frame_buffer_object);
}

Texture__Frame_Buffer::~Texture__Frame_Buffer()
{
    glDeleteFramebuffers(1, &m_frame_buffer_object);

    if(m_depth_texture_object != 0)
        glDeleteTextures(1, &m_depth_texture_object);
}



void Texture__Frame_Buffer::set_size(unsigned int _width, unsigned int _height)
{
    m_width = _width;
    m_height = _height;

    LR::Binds_Controller::instance().bind_texture(bind_index(), opengl_texture_object());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    LR::Binds_Controller::instance().bind_frame_buffer(m_frame_buffer_object);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, opengl_texture_object(), 0);
    LR::Binds_Controller::instance().bind_frame_buffer(0);
}

void Texture__Frame_Buffer::set_should_clear_depth_bit(bool _value)
{
    m_should_clear_depth_bit = _value;

    m_clear_hint = GL_COLOR_BUFFER_BIT;
    if(!m_should_clear_depth_bit)
        return;

    m_clear_hint |= GL_DEPTH_BUFFER_BIT;

    if(m_depth_texture_object != 0)
        glDeleteTextures(1, &m_depth_texture_object);

    glGenTextures(1, &m_depth_texture_object);
    glBindTexture(GL_TEXTURE_2D, m_depth_texture_object);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    LR::Binds_Controller::instance().bind_frame_buffer(m_frame_buffer_object);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_object);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_texture_object, 0);
    LR::Binds_Controller::instance().bind_frame_buffer(0);
}

void Texture__Frame_Buffer::set_clear_color(const glm::vec4& _color)
{
    m_clear_color = _color;

    glClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2], m_clear_color[3]);
}





void Texture__Frame_Buffer::render()
{
    L_ASSERT(m_draw_func);

    LR::Binds_Controller& binds_controller = LR::Binds_Controller::instance();
    LR::Binds_Controller::OpenGL_State opengl_state = binds_controller.save_state();

    int viewport_data[4];
    glGetIntegerv(GL_VIEWPORT, viewport_data);
    glViewport(0, 0, m_width, m_height);

    binds_controller.bind_frame_buffer(m_frame_buffer_object);
    glClear(m_clear_hint);
    m_draw_func();

    binds_controller.restore_state(opengl_state);

    glViewport(viewport_data[0], viewport_data[1], viewport_data[2], viewport_data[3]);
}

void Texture__Frame_Buffer::prepare_to_draw()
{
    if(m_render_each_frame)
        render();

    Parent_Type::prepare_to_draw();
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Texture_Stub__Frame_Buffer)

BUILDER_STUB_INITIALIZATION_FUNC(Texture_Stub__Frame_Buffer)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_size(draw_area_width, draw_area_height);
    product->set_clear_color({clear_color_red, clear_color_green, clear_color_blue, clear_color_alpha});
    product->set_should_clear_depth_bit(clear_depth_bit);
    product->set_render_each_frame(render_each_frame);
}
