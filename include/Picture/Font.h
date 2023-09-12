#ifndef FONT_H
#define FONT_H

#include <Variable_Base.h>

#include <Picture/Picture.h>


namespace LR
{

    class Letter_Data : public LV::Variable_Base
    {
    public:
        DECLARE_VARIABLE;

    public:
        unsigned char letter = 0;
        float pos_x = 0.0f, pos_y = 0.0f;
        float size_x = 0.0f, size_y = 0.0f;

    };

    class Font
    {
    private:
        const Picture* m_picture = nullptr;

    private:
        Letter_Data m_letters[256];

    private:
        Font();
        friend Font* load_font(const std::string& _path);

    public:
        Font(const Font&) = delete;
        Font(Font&&) = delete;

    public:
        ~Font();

    public:
        const Letter_Data& get_letter_data(unsigned char _letter) const;
        bool has_letter(unsigned char _letter) const;

    public:
        inline const Picture* picture() const { return m_picture; }

    };

    Font* load_font(const std::string& _path);

}

#endif // FONT_H
