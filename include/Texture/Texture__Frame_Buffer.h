#pragma once

#include <vec4.hpp>

#include <Texture/Texture.h>


namespace LR
{

class Texture__Frame_Buffer : public LR::Texture
{
public:
    INIT_VARIABLE(LR::Texture__Frame_Buffer, LR::Texture)

public:
    using Draw_Func = LST::Function<void()>;

private:
    unsigned int m_frame_buffer_object = 0;
    unsigned int m_clear_hint = 0;

    unsigned int m_depth_texture_object = 0;

    glm::vec4 m_clear_color;
    bool m_should_clear_depth_bit = false;

    Draw_Func m_draw_func;

    bool m_render_each_frame = true;

public:
    Texture__Frame_Buffer();
    ~Texture__Frame_Buffer();

public:
    inline void set_draw_func(const Draw_Func& _func) { m_draw_func = _func; }
    inline void set_render_each_frame(bool _value) { m_render_each_frame = _value; }

    inline unsigned int opengl_frame_buffer_object() const { return m_frame_buffer_object; }
    inline const glm::vec4& clear_color() const { return m_clear_color; }

public:
    void set_size(unsigned int _width, unsigned int _height);
    void set_should_clear_depth_bit(bool _value);
    void set_clear_color(const glm::vec4& _color);

public:
    void render();
    void prepare_to_draw() override;

};


class Texture_Stub__Frame_Buffer : public LR::Texture_Stub
{
public:
    INIT_VARIABLE(LR::Texture_Stub__Frame_Buffer, LR::Texture_Stub)

    INIT_FIELDS
    ADD_FIELD(unsigned int, draw_area_width)
    ADD_FIELD(unsigned int, draw_area_height)
    ADD_FIELD(float, clear_color_red)
    ADD_FIELD(float, clear_color_green)
    ADD_FIELD(float, clear_color_blue)
    ADD_FIELD(float, clear_color_alpha)
    ADD_FIELD(bool, clear_depth_bit)
    ADD_FIELD(bool, render_each_frame)
    FIELDS_END

public:
    unsigned int draw_area_width = 0;
    unsigned int draw_area_height = 0;
    float clear_color_red = 0.0f;       //  too lazy to add vec4 type to type manager. maybe should fix it later
    float clear_color_green = 0.0f;
    float clear_color_blue = 0.0f;
    float clear_color_alpha = 0.0f;
    bool clear_depth_bit = false;
    bool render_each_frame = true;

public:
    INIT_BUILDER_STUB(Texture__Frame_Buffer)

};

}
