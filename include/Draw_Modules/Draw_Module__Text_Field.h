#ifndef DRAW_MODULE__TEXT_FIELD_H
#define DRAW_MODULE__TEXT_FIELD_H

#include <Math_Stuff.h>

#include <Draw_Modules/Draw_Module_Base.h>
#include <Picture/Font.h>
#include <Picture/Graphic_Resources_Manager.h>


namespace LR
{

    class Draw_Module__Text_Field__Stub : public Draw_Module_Base_Stub
    {
    public:
        DECLARE_VARIABLE;

    public:
        const LR::Graphic_Resources_Manager* graphic_resources_manager = nullptr;

    public:
        std::string font_name;
        unsigned int horizontal_alignment = 0;
        unsigned int vertical_alignment = 0;
        glm::vec3 raw_offset{0.0f, 0.0f, 0.0f};
        float max_size = -1.0f;     //  negative value means no limit
        std::string text;

    protected:
        LV::Variable_Base* M_construct_product() const override;
        void M_init_constructed_product(LV::Variable_Base* _product) const override;

    };



    class Text_Field_Settings
    {
    public:
        enum class Horizontal_Alignment
        {
            Left = 0,
            Right = 1,
            Center = 2
        };
        enum class Vertical_Alignment
        {
            Bottom = 0,
            Top = 1,
            Center = 2
        };

        const Font* font = nullptr;

        Horizontal_Alignment horizontal_alignment = Horizontal_Alignment::Left;
        Vertical_Alignment vertical_alignment = Vertical_Alignment::Bottom;

        glm::vec3 raw_offset{0.0f, 0.0f, 0.0f};
        //  1.0f means whole string will fit inside 1 x 1 square ( hope it makes sence ). in other words, proportionally shrinks/stretches result string so width or height are not larger then max_size...
        float max_size = 1.0f;

        std::string text;

    public:
        bool operator==(const Text_Field_Settings& _other) const;
        bool operator!=(const Text_Field_Settings& _other) const;

    };

    class Draw_Module__Text_Field : public Draw_Module_Base
    {
    public:
        DECLARE_VARIABLE;

    private:
        Text_Field_Settings m_configurable_settings;    //  settings, configurable from outside of object
        Text_Field_Settings m_current_settings;         //  settings for current configuration

    public:
        inline unsigned int gl_draw_mode() const override { return GL_TRIANGLES; }

    public:
        inline Text_Field_Settings& settings() { return m_configurable_settings; }
        inline const Text_Field_Settings& settings() const { return m_configurable_settings; }

    private:
        glm::vec2 M_calculate_raw_size() const;
        float M_calculate_raw_scale() const;

        void M_construct_coords(float* _coords, unsigned int _amount, unsigned int _amount_per_character);
        void M_construct_colors(float* _colors, unsigned int _amount);
        void M_construct_texture_coords(float* _texture_coords, unsigned int _amount, unsigned int _amount_per_character);

        void M_reconfigure();

    public:
        void update(float _dt) override;

    };

}

#endif // DRAW_MODULE__TEXT_FIELD_H
