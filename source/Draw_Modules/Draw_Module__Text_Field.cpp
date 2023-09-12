#include <Draw_Modules/Draw_Module__Text_Field.h>

using namespace LR;


INIT_FIELDS(LR::Draw_Module__Text_Field__Stub, LV::Builder_Stub)
FIELDS_END



LV::Variable_Base* Draw_Module__Text_Field__Stub::M_construct_product() const
{
    return new Draw_Module__Text_Field();
}

void Draw_Module__Text_Field__Stub::M_init_constructed_product(LV::Variable_Base *_product) const
{
    LV::Builder_Stub::M_init_constructed_product(_product);

    Draw_Module__Text_Field* product = (Draw_Module__Text_Field*)_product;

    Text_Field_Settings& tfs = product->settings();
    tfs.font = graphic_resources_manager->get_font(font_name);
    tfs.text = text;
    tfs.max_size = max_size;
    tfs.raw_offset = raw_offset;

    L_ASSERT(horizontal_alignment <= 2);
    L_ASSERT(vertical_alignment <= 2);

    tfs.horizontal_alignment = (Text_Field_Settings::Horizontal_Alignment)horizontal_alignment;
    tfs.vertical_alignment = (Text_Field_Settings::Vertical_Alignment)vertical_alignment;
}





bool Text_Field_Settings::operator==(const Text_Field_Settings &_other) const
{
    return  font == _other.font &&
            horizontal_alignment == _other.horizontal_alignment &&
            vertical_alignment == _other.vertical_alignment &&
            LEti::Math::vecs_are_equal(raw_offset, _other.raw_offset) &&
            LEti::Math::floats_are_equal(max_size, _other.max_size) &&
            text == _other.text;
}





INIT_FIELDS(LR::Draw_Module__Text_Field, LR::Draw_Module_Base)
FIELDS_END



glm::vec2 Draw_Module__Text_Field::M_calculate_raw_size() const
{
    glm::vec2 result;

    if(m_current_settings.text.size() == 0)
        return result;

    result.x = m_current_settings.font->get_letter_data(m_current_settings.text[0]).size_x;
    result.y = m_current_settings.font->get_letter_data(m_current_settings.text[0]).size_y;

    for(unsigned int i=1; i<m_current_settings.text.size(); ++i)
    {
        result.x += m_current_settings.font->get_letter_data(m_current_settings.text[i]).size_x;
        float ch = m_current_settings.font->get_letter_data(m_current_settings.text[i]).size_y;
        if(ch > result.y)
            result.y = ch;
    }

    return result;
}


void Draw_Module__Text_Field::M_construct_coords(float *_coords, unsigned int _amount, unsigned int _amount_per_character)
{
    L_ASSERT(vertices().floats_per_vertex() > 1);    //  single-dimentional font is not supported :D

    for(unsigned int i=0; i<_amount; ++i)
        _coords[i] = 0.0f;

    float

    float current_width = 0.0f;

    auto construct_character = [this, &current_width](float* _array, unsigned int _character_index)
    {
        unsigned int fpv = vertices().floats_per_vertex();
        const Letter_Data& letter_data = m_current_settings.font->get_letter_data(m_current_settings.text[_character_index]);

        _array[(fpv * 0) + 0] = current_width;                             _array[(fpv * 0) + 1] = letter_data.size_y;
        _array[(fpv * 1) + 0] = current_width;                             _array[(fpv * 1) + 1] = 0.0f;
        _array[(fpv * 2) + 0] = current_width + letter_data.size_x;        _array[(fpv * 2) + 1] = 0.0f;
        _array[(fpv * 3) + 0] = current_width;                             _array[(fpv * 3) + 1] = letter_data.size_y;
        _array[(fpv * 4) + 0] = current_width + letter_data.size_x;        _array[(fpv * 4) + 1] = 0.0f;
        _array[(fpv * 5) + 0] = current_width + letter_data.size_x;        _array[(fpv * 5) + 1] = letter_data.size_x;

        current_width += letter_data.size_x;
    };

    for(unsigned int i=0; i<m_current_settings.text.size(); ++i)
    {
        float* array_with_offset = &(_coords[i * _amount_per_character]);
        construct_character(array_with_offset, i);
    }
}


void Draw_Module__Text_Field::M_reconfigure()
{
    m_current_settings = m_configurable_settings;

    const unsigned int texture_coords_per_character = vertices().floats_per_vertex() * 6;
    const unsigned int coords_per_character = texture().floats_per_vertex() * 6;
    const unsigned int colors_per_character = colors().floats_per_vertex() * 6;

    unsigned int texture_coords_amount = texture_coords_per_character * m_current_settings.text.size();
    unsigned int coords_amount = coords_per_character * m_current_settings.text.size();
    unsigned int colors_amount = colors_per_character * m_current_settings.text.size();

    float* texture_coords = new float[texture_coords_amount];
    float* coords = new float[coords_amount];
    float* colors = new float[colors_amount];


}






























































