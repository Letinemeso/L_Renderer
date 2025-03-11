#include <Texture/Texture__Frame_Buffer.h>

using namespace LR;


Texture__Frame_Buffer::Texture__Frame_Buffer() : Texture()
{
    glGenFramebuffers(1, &m_frame_buffer_object);
}

Texture__Frame_Buffer::~Texture__Frame_Buffer()
{
    glDeleteFramebuffers(1, &m_frame_buffer_object);
}



void Texture__Frame_Buffer::set_size(unsigned int _width, unsigned int _height)
{
    m_width = _width;
    m_height = _height;

    glBindTexture(GL_TEXTURE_2D, opengl_texture_object());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_object);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, opengl_texture_object(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Texture__Frame_Buffer::set_should_clear_depth_bit(bool _value)
{
    m_should_clear_depth_bit = _value;

    m_clear_hint = GL_COLOR_BUFFER_BIT;
    if(m_should_clear_depth_bit)
        m_clear_hint |= GL_DEPTH_BUFFER_BIT;
}

void Texture__Frame_Buffer::set_clear_color(const glm::vec4& _color)
{
    m_clear_color = _color;

    glClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2], m_clear_color[3]);
}



Texture__Frame_Buffer::OpenGL_State Texture__Frame_Buffer::M_save_opengl_state() const
{
    OpenGL_State result;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &result.vertex_array);
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &result.frame_buffer);

    int textures_amount = 0;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textures_amount);

    result.bound_textures.resize_and_fill(textures_amount, 0);
    for(unsigned int i=0; i<textures_amount; ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        int bound_texture = 0;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &bound_texture);

        result.bound_textures[i] = bound_texture;
    }

    return result;
}

void Texture__Frame_Buffer::M_restore_opengl_state(const OpenGL_State& _state) const
{
    glBindVertexArray(_state.vertex_array);
    glBindFramebuffer(GL_FRAMEBUFFER, _state.frame_buffer);

    for(unsigned int i=0; i<_state.bound_textures.size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, _state.bound_textures[i]);
    }
}



void Texture__Frame_Buffer::render()
{
    L_ASSERT(m_draw_func);

    OpenGL_State opengl_state = M_save_opengl_state();

    glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_object);
    glClear(m_clear_hint);
    m_draw_func();

    if(bind_index() == 0)
    {
        GLubyte data[4];
        glReadPixels(960, 540, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
        std::cout << "red: " << (int)data[0] << " green: " << (int)data[1] << " blue: " << (int)data[2] << " alpha: " << (int)data[3] << std::endl;
    }

    M_restore_opengl_state(opengl_state);
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
