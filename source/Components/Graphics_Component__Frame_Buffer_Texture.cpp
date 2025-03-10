#include <Components/Graphics_Component__Frame_Buffer_Texture.h>

using namespace LR;


Graphics_Component__Frame_Buffer_Texture::Graphics_Component__Frame_Buffer_Texture()
{
    glGenFramebuffers(1, &m_frame_buffer_object);
}


Graphics_Component__Frame_Buffer_Texture::~Graphics_Component__Frame_Buffer_Texture()
{
    glDeleteTextures(1, &m_texture_object);
    glDeleteFramebuffers(1, &m_frame_buffer_object);
}



void Graphics_Component__Frame_Buffer_Texture::set_texture_bind_index(unsigned int _value)
{
    m_texture_bind_index = GL_TEXTURE0 + _value;
    L_ASSERT(m_texture_bind_index < GL_MAX_TEXTURE_UNITS);
}

void Graphics_Component__Frame_Buffer_Texture::init_texture(const Settings& _settings)
{
    glDeleteTextures(1, &m_texture_object);

    glGenTextures(1, &m_texture_object);
    glBindTexture(GL_TEXTURE_2D, m_texture_object);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _settings.min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _settings.mag_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _settings.wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _settings.wrap_t);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _settings.width, _settings.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_object);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture_object, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_clear_hint = GL_COLOR_BUFFER_BIT;
    if(_settings.clear_depth_bit)
        m_clear_hint = m_clear_hint | GL_DEPTH_BUFFER_BIT;

    glClearColor(_settings.clear_color[0], _settings.clear_color[1], _settings.clear_color[2], _settings.clear_color[3]);
}



Graphics_Component__Frame_Buffer_Texture::OpenGL_State Graphics_Component__Frame_Buffer_Texture::M_save_opengl_state() const
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

void Graphics_Component__Frame_Buffer_Texture::M_restore_opengl_state(const OpenGL_State& _state) const
{
    glBindVertexArray(_state.vertex_array);
    glBindFramebuffer(GL_FRAMEBUFFER, _state.frame_buffer);

    for(unsigned int i=0; i<_state.bound_textures.size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, _state.bound_textures[i]);
    }
}



void Graphics_Component__Frame_Buffer_Texture::update(float _dt) const
{
    Graphics_Component::update(_dt);

    if(m_update_func)
        m_update_func(_dt);
}

void Graphics_Component__Frame_Buffer_Texture::prepare_to_draw() const
{
    Parent_Type::prepare_to_draw();

    L_ASSERT(m_texture_object);
    L_ASSERT(m_frame_buffer_object);
    L_ASSERT(m_draw_func);

    OpenGL_State opengl_state = M_save_opengl_state();

    glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_object);
    glClear(m_clear_hint);
    m_draw_func();

    M_restore_opengl_state(opengl_state);

    glActiveTexture(m_texture_bind_index);
    glBindTexture(GL_TEXTURE_2D, m_texture_object);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Graphics_Component_Stub__Frame_Buffer_Texture)

BUILDER_STUB_INITIALIZATION_FUNC(Graphics_Component_Stub__Frame_Buffer_Texture)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_texture_bind_index(texture_bind_index);

    Graphics_Component__Frame_Buffer_Texture::Settings settings = M_parse_settings();
    product->init_texture(settings);
}



Graphics_Component__Frame_Buffer_Texture::Settings Graphics_Component_Stub__Frame_Buffer_Texture::M_parse_settings() const
{
    Graphics_Component__Frame_Buffer_Texture::Settings result;

    if(min_filter == "Nearest")
        result.min_filter = GL_NEAREST;
    else if(min_filter == "Linear")
        result.min_filter = GL_LINEAR;
    else
    {
        L_ASSERT(false);    //  haven't used any other type yet, so just add them here if needed
    }

    if(mag_filter == "Nearest")
        result.mag_filter = GL_NEAREST;
    else if(mag_filter == "Linear")
        result.mag_filter = GL_LINEAR;
    else
    {
        L_ASSERT(false);    //  haven't used any other type yet, so just add them here if needed
    }

    if(wrap_s == "Repeat")
        result.wrap_s = GL_CLAMP_TO_EDGE;
    else if(wrap_s == "Clamp_To_Edge")
        result.wrap_s = GL_REPEAT;
    else
    {
        L_ASSERT(false);    //  haven't used any other type yet, so just add them here if needed
    }

    if(wrap_t == "Repeat")
        result.wrap_t = GL_CLAMP_TO_EDGE;
    else if(wrap_t == "Clamp_To_Edge")
        result.wrap_t = GL_REPEAT;
    else
    {
        L_ASSERT(false);    //  haven't used any other type yet, so just add them here if needed
    }

    result.width = draw_area_width;
    result.height = draw_area_height;

    result.clear_color[0] = clear_color_red;
    result.clear_color[1] = clear_color_green;
    result.clear_color[2] = clear_color_blue;
    result.clear_color[3] = clear_color_alpha;

    result.clear_depth_bit = clear_depth_bit;

    return result;
}
