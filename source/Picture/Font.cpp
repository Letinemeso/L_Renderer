#include <Picture/Font.h>

using namespace LR;


Font::Font()
{

}



Font::~Font()
{
    delete m_picture;
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





Font* LR::load_font(const std::string& _path)
{
    LV::MDL_Reader reader;
    reader.parse_file(_path);

    L_ASSERT(reader.stubs().size() == 1);

    Font* result = new Font();

    const LV::MDL_Variable_Stub& stub = *reader.stubs().iterator();

    for(LDS::Map<std::string, LV::MDL_Variable_Stub>::Const_Iterator it = stub.childs.iterator(); !it.end_reached(); ++it)
    {
        L_ASSERT(it.key().size() == 1);

        unsigned char letter = it.key()[0];
        Letter_Data& letter_data = result->m_letters[letter];
        letter_data.letter = letter;
        letter_data.assign_values(*it);
    }

    LDS::Map<std::string, LDS::Vector<std::string>>::Const_Iterator texture_path_it = stub.fields.find("picture_path");
    L_ASSERT(texture_path_it->size() == 1);

    result->m_picture = load_picture((*texture_path_it)[0]);
    L_ASSERT(result->m_picture);

    return result;
}
