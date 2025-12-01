#include <Texture/Texture__Frame_Buffer.h>

#include <glew.h>

#include <Binds_Controller/Binds_Controller.h>

using namespace LR;


Texture__Frame_Buffer::Texture__Frame_Buffer() : Texture(), m_clear_hint(GL_COLOR_BUFFER_BIT)
{
    glGenFramebuffers(1, &m_frame_buffer_object);

    GLint max_attachments = 0;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &max_attachments);
    m_color_attachments.resize_and_fill(max_attachments, 0);
}

Texture__Frame_Buffer::~Texture__Frame_Buffer()
{
    glDeleteFramebuffers(1, &m_frame_buffer_object);

    if(m_depth_texture_object != 0)
        glDeleteTextures(1, &m_depth_texture_object);

    for(unsigned int i = 0; i < m_color_attachments.size(); ++i)
    {
        if(m_color_attachments[i] == 0)
            continue;

        glDeleteTextures(1, &m_color_attachments[i]);
    }
}



void Texture__Frame_Buffer::M_reconfigure_color_attachments()
{
    LR::Binds_Controller::instance().bind_frame_buffer(m_frame_buffer_object);

    for(unsigned int i = 0; i < m_color_attachments.size(); ++i)
    {
        unsigned int handle = m_color_attachments[i];
        if(handle == 0)
            continue;

        LR::Binds_Controller::instance().bind_texture(i, handle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, handle, 0);
    }

    LR::Binds_Controller::instance().bind_frame_buffer(0);
}

void Texture__Frame_Buffer::M_reconfigure_depth_buffer()
{
    if(m_depth_texture_object != 0)
        glDeleteTextures(1, &m_depth_texture_object);

    LR::Binds_Controller::instance().bind_frame_buffer(m_frame_buffer_object);

    glGenTextures(1, &m_depth_texture_object);
    glBindTexture(GL_TEXTURE_2D, m_depth_texture_object);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_texture_object, 0);

    glEnable(GL_DEPTH_TEST);

    LR::Binds_Controller::instance().bind_frame_buffer(0);
}

void Texture__Frame_Buffer::M_prepare_draw_buffers()
{
    unsigned int amount = 0;
    unsigned int buffer_ids[64];
    for(unsigned int i = 0; i < m_color_attachments.size(); ++i)
    {
        if(m_color_attachments[i] == 0)
            continue;

        buffer_ids[amount] = GL_COLOR_ATTACHMENT0 + i;
        ++amount;
    }

    glDrawBuffers(amount, buffer_ids);
}

void Texture__Frame_Buffer::M_reset_draw_buffers()
{
    unsigned int Back_Buffer = GL_BACK_LEFT;
    glDrawBuffers(1, &Back_Buffer);
}



void Texture__Frame_Buffer::set_size(unsigned int _width, unsigned int _height)
{
    m_width = _width;
    m_height = _height;

    M_reconfigure_color_attachments();

    if(m_should_clear_depth_bit)
        M_reconfigure_depth_buffer();
}

void Texture__Frame_Buffer::set_should_clear_depth_bit(bool _value)
{
    m_should_clear_depth_bit = _value;

    m_clear_hint = GL_COLOR_BUFFER_BIT;
    if(m_should_clear_depth_bit)
    {
        m_clear_hint |= GL_DEPTH_BUFFER_BIT;
        M_reconfigure_depth_buffer();
    }
    else if(m_depth_texture_object != 0)
    {
        LR::Binds_Controller::instance().bind_frame_buffer(m_frame_buffer_object);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_texture_object, 0);
        glDisable(GL_DEPTH_TEST);
        LR::Binds_Controller::instance().bind_frame_buffer(0);

        glDeleteTextures(1, &m_depth_texture_object);
    }
}

void Texture__Frame_Buffer::set_clear_color(const glm::vec4& _color)
{
    m_clear_color = _color;

    glClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2], m_clear_color[3]);
}

void Texture__Frame_Buffer::enable_color_attachment(unsigned int _index)
{
    L_ASSERT(_index < m_color_attachments.size());
    L_ASSERT(m_color_attachments[_index] == 0);

    LR::Binds_Controller::instance().bind_frame_buffer(m_frame_buffer_object);

    unsigned int& handle = m_color_attachments[_index];

    glGenTextures(1, &handle);

    LR::Binds_Controller::instance().bind_texture(_index, handle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _index, GL_TEXTURE_2D, handle, 0);

    LR::Binds_Controller::instance().bind_frame_buffer(0);
}

void Texture__Frame_Buffer::disable_color_attachment(unsigned int _index)
{
    L_ASSERT(m_color_attachments[_index] != 0);

    LR::Binds_Controller::instance().bind_frame_buffer(m_frame_buffer_object);

    unsigned int& handle = m_color_attachments[_index];

    glDeleteTextures(1, &handle);
    handle = 0;

    LR::Binds_Controller::instance().bind_frame_buffer(0);
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

    M_prepare_draw_buffers();

    glClear(m_clear_hint);
    m_draw_func();

    binds_controller.restore_state(opengl_state);
    M_reset_draw_buffers();

    glViewport(viewport_data[0], viewport_data[1], viewport_data[2], viewport_data[3]);
}

void Texture__Frame_Buffer::prepare_to_draw()
{
    if(m_render_each_frame)
        render();

    for(unsigned int i = 0; i < m_color_attachments.size(); ++i)
    {
        if(m_color_attachments[i] == 0)
            continue;

        LR::Binds_Controller::instance().bind_texture(i, m_color_attachments[i]);
    }
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

    for(unsigned int i = 0; i < color_attachments.size(); ++i)
        product->enable_color_attachment(color_attachments[i]);
}
