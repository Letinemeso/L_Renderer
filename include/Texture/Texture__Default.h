#pragma once

#include <Resources_Manager.h>

#include <Texture/Texture.h>
#include <Resources/Picture.h>


namespace LR
{

    class Texture__Default : public LR::Texture
    {
    public:
        INIT_VARIABLE(LR::Texture__Default, LR::Texture)

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
        Texture__Default();
        ~Texture__Default();

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
        void create_from_picture(const Picture* _picture);
        void set_picture(const Picture* _picture);

    public:
        void prepare_to_draw() override;

    };


    class Texture_Stub__Default : public LR::Texture_Stub
    {
    public:
        INIT_VARIABLE(LR::Texture_Stub__Default, LR::Texture_Stub)

        INIT_FIELDS
        ADD_FIELD(unsigned int, bind_index)
        ADD_FIELD(std::string, min_filter)
        ADD_FIELD(std::string, mag_filter)
        ADD_FIELD(std::string, wrap_s)
        ADD_FIELD(std::string, wrap_t)
        ADD_FIELD(std::string, picture_name)
        FIELDS_END

        INIT_CHILDS
        ADD_CHILD("picture", picture_stub)
        CHILDS_END

        OVERRIDE_ON_VALUES_ASSIGNED

    public:
        LST::Function<const LEti::Resources_Manager*()> resources_manager_getter;

    public:
        unsigned int bind_index = 0;
        std::string min_filter = "Nearest";
        std::string mag_filter = "Nearest";
        std::string wrap_s = "Repeat";
        std::string wrap_t = "Repeat";
        std::string picture_name;       //  if name size() != 0, stub will attempt to get picture as resource from resources manager

        LR::Picture_Stub* picture_stub = nullptr;       //  if this is initialized on stub creation, picture will be stored and deleted by stub itself. incompatible with using picture as resource
        LR::Picture* picture = nullptr;

    public:
        INIT_BUILDER_STUB(Texture__Default)

    public:
        void apply_settings(Texture__Default* _product) const;

    public:
        ~Texture_Stub__Default();

    };

}
