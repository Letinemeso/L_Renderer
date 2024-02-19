#include <Resources/Font.h>

using namespace LR;


Font::Font()
{

}



Font::~Font()
{

}



const Letter_Data& Font::get_letter_data(unsigned char _letter) const
{
    L_ASSERT(_letter != 0);
    L_ASSERT(m_letters[_letter].letter == _letter);

    return m_letters[_letter];
}

bool Font::has_letter(unsigned char _letter) const
{
    L_ASSERT(_letter != 0);

    return m_letters[_letter].letter == _letter;
}





Font_Stub::~Font_Stub()
{
    for(LV::Variable_Base::Childs_List::Iterator it = letters_data.begin(); !it.end_reached(); ++it)
        delete it->child_ptr;
}



BUILDER_STUB_CONSTRUCTION_FUNC(Font_Stub) BUILDER_STUB_CONSTRUCTION_FUNC_DEFAULT_IMPL

BUILDER_STUB_INITIALIZATION_FUNC(Font_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    for(LV::Variable_Base::Childs_List::Const_Iterator it = letters_data.begin(); !it.end_reached(); ++it)
    {
        L_ASSERT(it->name.size() == 1);

        Letter_Data* letter = LV::cast_variable<Letter_Data>(it->child_ptr);
        L_ASSERT(letter);

        Letter_Data& products_letter_data = product->m_letters[it->name[0]];

        L_ASSERT(products_letter_data.letter == 0);   //  letter duplicate    (more 'letter's!!!)

        products_letter_data = *letter;
        products_letter_data.letter = it->name[0];
    }
}
