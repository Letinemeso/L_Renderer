#pragma once

#include <Resources_Manager.h>

#include <Texture/Texture.h>
#include <Resources/Picture.h>


namespace LR
{

    class Texture__Preloaded : public LR::Texture
    {
    public:
        INIT_VARIABLE(LR::Texture__Preloaded, LR::Texture)

    public:
        struct Settings
        {
            int min_filter;
            int mag_filter;
            int wrap_s;
            int wrap_t;

            Settings();
        };

    private:
        unsigned int m_texture_object = 0;
        unsigned int m_bind_index = 0;
        Settings m_current_settings;

    private:
        unsigned int m_width = 0;
        unsigned int m_height = 0;

    private:
        const Picture* m_picture = nullptr;

    public:
        Texture__Preloaded();
        ~Texture__Preloaded();

    public:
        inline unsigned int opengl_texture_object() const { return m_texture_object; }
        inline unsigned int bind_index() const { return m_bind_index; }
        inline const Settings& settings() const { return m_current_settings; }
        inline unsigned int width() const { return m_width; }
        inline unsigned int height() const { return m_height; }

        inline const Picture* picture() const { return m_picture; }

    public:
        void set_settings(const Settings& _settings);
        void set_bind_index(unsigned int _index);

    public:
        void set_picture(const Picture* _picture);

    public:
        void prepare_to_draw() override;

    };


    class Texture_Stub__Preloaded : public LR::Texture_Stub
    {
    public:
        INIT_VARIABLE(LR::Texture_Stub__Preloaded, LR::Texture_Stub)

        INIT_FIELDS
        ADD_FIELD(unsigned int, bind_index)
        ADD_FIELD(std::string, min_filter)
        ADD_FIELD(std::string, mag_filter)
        ADD_FIELD(std::string, wrap_s)
        ADD_FIELD(std::string, wrap_t)
        ADD_FIELD(std::string, picture_name)
        FIELDS_END

    public:
        const LEti::Resources_Manager* resources_manager = nullptr;

    public:
        unsigned int bind_index = 0;
        std::string min_filter = "Nearest";
        std::string mag_filter = "Nearest";
        std::string wrap_s = "Repeat";
        std::string wrap_t = "Repeat";
        std::string picture_name;

    public:
        INIT_BUILDER_STUB(Texture__Preloaded)

    public:
        void apply_settings(Texture__Preloaded* _product) const;

    };

}
