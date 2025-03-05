#pragma once

#include <L_Debug/L_Debug.h>

#include <Resources_Manager.h>

#include <Components/Graphics_Component.h>
#include <Resources/Picture.h>

namespace LR
{

    class Graphics_Component__Texture final : public Graphics_Component
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component__Texture, LR::Graphics_Component)

    public:
        struct Texture_Settings
        {
            int min_filter = GL_NEAREST;
            int mag_filter = GL_NEAREST;
            int wrap_s = GL_REPEAT;
            int wrap_t = GL_REPEAT;

            Texture_Settings() { }
        };

    private:
        const LEti::Resources_Manager* m_resources_manager = nullptr;

    private:
        unsigned int m_texture_object = 0;
        const Picture* m_picture = nullptr;

    public:
        Graphics_Component__Texture();
        Graphics_Component__Texture(const Graphics_Component__Texture&) = delete;
        Graphics_Component__Texture(Graphics_Component__Texture&&) = delete;
        void operator=(const Graphics_Component__Texture&) = delete;
        void operator=(Graphics_Component__Texture&&) = delete;

        ~Graphics_Component__Texture();

    public:
        inline void inject_resources_manager(const LEti::Resources_Manager* _ptr) { m_resources_manager = _ptr; }
        inline const LEti::Resources_Manager* resources_manager() const { return m_resources_manager; }

    public:
        void set_picture(const Picture* _picture, const Texture_Settings& _settings = Texture_Settings());
        void reconfigure_texture_coords();

    public:
        inline const Picture* get_picture() const { return m_picture; }

    public:
        void update(float _dt) const override;
        void prepare_to_draw() const override;

    };


    class Graphics_Component_Stub__Texture : public Graphics_Component_Stub
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component_Stub__Texture, LR::Graphics_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, picture_name)
        ADD_FIELD(bool, texture_coords_in_pixels)
        ADD_FIELD(std::string, min_filter)
        ADD_FIELD(std::string, mag_filter)
        ADD_FIELD(std::string, wrap_s)
        ADD_FIELD(std::string, wrap_t)
        FIELDS_END

    public:
        const LEti::Resources_Manager* resources_manager = nullptr;

    public:
        std::string picture_name;
        bool texture_coords_in_pixels = true;
        std::string min_filter = "Nearest";
        std::string mag_filter = "Nearest";
        std::string wrap_s = "Repeat";
        std::string wrap_t = "Repeat";

    protected:
        INIT_BUILDER_STUB(Graphics_Component__Texture)

    private:
        Graphics_Component__Texture::Texture_Settings M_parse_settings() const;

    };

}
