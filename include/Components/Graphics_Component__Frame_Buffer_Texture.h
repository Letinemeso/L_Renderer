#pragma once

#include <L_Debug/L_Debug.h>

#include <Stuff/Function_Wrapper.h>

#include <vec2.hpp>
#include <vec4.hpp>

#include <Components/Graphics_Component.h>

namespace LR
{

    class Graphics_Component__Frame_Buffer_Texture final : public Graphics_Component
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component__Frame_Buffer_Texture, LR::Graphics_Component)

    public:
        struct Settings
        {
            int min_filter = GL_NEAREST;
            int mag_filter = GL_NEAREST;
            int wrap_s = GL_REPEAT;
            int wrap_t = GL_REPEAT;

            unsigned int width = 0;
            unsigned int height = 0;

            glm::vec4 clear_color = {0.0f, 0.0f, 0.0f, 0.0f};
            bool clear_depth_bit = false;

            Settings() { }
        };

        using Update_Func = LST::Function<void(float)>;
        using Draw_Func = LST::Function<void()>;

    private:
        unsigned int m_texture_object = 0;
        unsigned int m_frame_buffer_object = 0;

        unsigned int m_clear_hint = 0;

        Update_Func m_update_func;
        Draw_Func m_draw_func;

    public:
        Graphics_Component__Frame_Buffer_Texture();
        Graphics_Component__Frame_Buffer_Texture(const Graphics_Component__Frame_Buffer_Texture&) = delete;
        Graphics_Component__Frame_Buffer_Texture(Graphics_Component__Frame_Buffer_Texture&&) = delete;
        void operator=(const Graphics_Component__Frame_Buffer_Texture&) = delete;
        void operator=(Graphics_Component__Frame_Buffer_Texture&&) = delete;

        ~Graphics_Component__Frame_Buffer_Texture();

    public:
        inline void set_update_func(const Update_Func& _func) { m_update_func = _func; }
        inline void set_draw_func(const Draw_Func& _func) { m_draw_func = _func; }

    public:
        void init_texture(const Settings& _settings = Settings());

    public:
        void update(float _dt) const override;
        void prepare_to_draw() const override;

    };


    class Graphics_Component_Stub__Frame_Buffer_Texture : public Graphics_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component_Stub__Frame_Buffer_Texture, LR::Graphics_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, min_filter)
        ADD_FIELD(std::string, mag_filter)
        ADD_FIELD(std::string, wrap_s)
        ADD_FIELD(std::string, wrap_t)
        ADD_FIELD(unsigned int, draw_area_width)
        ADD_FIELD(unsigned int, draw_area_height)
        ADD_FIELD(float, clear_color_red)
        ADD_FIELD(float, clear_color_green)
        ADD_FIELD(float, clear_color_blue)
        ADD_FIELD(float, clear_color_alpha)
        ADD_FIELD(bool, clear_depth_bit)
        FIELDS_END

    public:
        std::string min_filter = "Nearest";
        std::string mag_filter = "Nearest";
        std::string wrap_s = "Repeat";
        std::string wrap_t = "Repeat";
        unsigned int draw_area_width = 0;
        unsigned int draw_area_height = 0;
        float clear_color_red = 0.0f;       //  too lazy to add vec4 type to type manager. maybe should fix it later
        float clear_color_green = 0.0f;
        float clear_color_blue = 0.0f;
        float clear_color_alpha = 0.0f;
        bool clear_depth_bit = false;

    protected:
        INIT_BUILDER_STUB(Graphics_Component__Frame_Buffer_Texture)

    private:
        Graphics_Component__Frame_Buffer_Texture::Settings M_parse_settings() const;

    };

}
