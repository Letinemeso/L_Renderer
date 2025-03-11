#pragma once

#include <L_Debug/L_Debug.h>

#include <Variable_Base.h>
#include <Builder_Stub.h>


namespace LR
{

    class Texture : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Texture, LV::Variable_Base)

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

    protected:
        unsigned int m_width = 0;
        unsigned int m_height = 0;

    public:
        Texture();
        ~Texture();

    public:
        inline unsigned int opengl_texture_object() const { return m_texture_object; }
        inline unsigned int bind_index() const { return m_bind_index; }
        inline const Settings& settings() const { return m_current_settings; }
        inline unsigned int width() const { return m_width; }
        inline unsigned int height() const { return m_height; }

    public:
        void set_settings(const Settings& _settings);
        void set_bind_index(unsigned int _index);

    public:
        virtual void prepare_to_draw();

    };


    class Texture_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Texture_Stub, LV::Builder_Stub)

        INIT_FIELDS
        ADD_FIELD(unsigned int, bind_index)
        ADD_FIELD(std::string, min_filter)
        ADD_FIELD(std::string, mag_filter)
        ADD_FIELD(std::string, wrap_s)
        ADD_FIELD(std::string, wrap_t)
        FIELDS_END

    public:
        unsigned int bind_index = 0;
        std::string min_filter = "Nearest";
        std::string mag_filter = "Nearest";
        std::string wrap_s = "Repeat";
        std::string wrap_t = "Repeat";

    public:
        INIT_BUILDER_STUB(Texture)

    private:
        void M_apply_settings(Constructed_Type* _product) const;

    };

}
