#pragma once

#include <Variable_Base.h>
#include <Builder_Stub.h>


namespace LR
{

    class Letter_Data : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Letter_Data, LV::Variable_Base)

        INIT_FIELDS
        ADD_FIELD(float, pos_x)
        ADD_FIELD(float, pos_y)
        ADD_FIELD(float, size_x)
        ADD_FIELD(float, size_y)
        FIELDS_END

    public:
        unsigned char letter = 0;
        float pos_x = 0.0f, pos_y = 0.0f;
        float size_x = 0.0f, size_y = 0.0f;

    };


    class Font : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Font, LV::Variable_Base)

    private:
        friend class Font_Stub;

    private:
        Letter_Data m_letters[256];

    protected:
        Font();

    public:
        ~Font();

    public:
        Font(const Font&) = delete;
        Font(Font&&) = delete;

    public:
        const Letter_Data& get_letter_data(unsigned char _letter) const;
        bool has_letter(unsigned char _letter) const;

    };


    class Font_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Font_Stub, LV::Builder_Stub)

        INIT_CHILDS_LISTS
        ADD_CHILDS_LIST("*", &letters_data)
        CHILDS_LISTS_END

    public:
        LV::Variable_Base::Childs_List letters_data;

    public:
        ~Font_Stub();

    public:
        INIT_BUILDER_STUB(Font)

    };

}
