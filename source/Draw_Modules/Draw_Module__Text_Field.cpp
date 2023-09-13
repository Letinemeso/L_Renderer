#include <Draw_Modules/Draw_Module__Text_Field.h>

using namespace LR;


INIT_FIELDS(LR::Draw_Module__Text_Field__Stub, LR::Draw_Module_Base_Stub)
ADD_FIELD(std::string, font_name)
ADD_FIELD(unsigned int, horizontal_alignment)
ADD_FIELD(unsigned int, vertical_alignment)
ADD_FIELD(glm::vec3, raw_offset)
ADD_FIELD(float, max_size)
ADD_FIELD(std::string, text)
FIELDS_END



LV::Variable_Base* Draw_Module__Text_Field__Stub::M_construct_product() const
{
    return new Draw_Module__Text_Field();
}

void Draw_Module__Text_Field__Stub::M_init_constructed_product(LV::Variable_Base *_product) const
{
    Draw_Module_Base_Stub::M_init_constructed_product(_product);

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

bool Text_Field_Settings::operator!=(const Text_Field_Settings &_other) const
{
    return !(*this == _other);
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

float Draw_Module__Text_Field::M_calculate_raw_scale() const
{
    if(m_current_settings.max_size < 0.0f)
        return 1.0f;

    glm::vec2 tf_raw_size = M_calculate_raw_size();
    float result = 1.0f;

    if(tf_raw_size.x > tf_raw_size.y)
        result = m_current_settings.max_size / tf_raw_size.x;
    else
        result = m_current_settings.max_size / tf_raw_size.y;

    return result;
}


void Draw_Module__Text_Field::M_construct_coords(float *_coords, unsigned int _amount, unsigned int _amount_per_character)
{
//    L_ASSERT(vertices().floats_per_vertex() > 1);    //  single-dimentional font is not supported :D

    for(unsigned int i=0; i<_amount; ++i)
        _coords[i] = 0.0f;

//    unsigned int fpv = vertices().floats_per_vertex();
    unsigned int fpv = 3;   //  this magic number should be taken from shader (or vertices) later

    float raw_scale = M_calculate_raw_scale();

    float current_width = 0.0f;

    auto construct_character = [this, &current_width, raw_scale, _coords, _amount_per_character, fpv](unsigned int _character_index)
    {
        float* array = &(_coords[_character_index * _amount_per_character]);

        const Letter_Data& letter_data = m_current_settings.font->get_letter_data(m_current_settings.text[_character_index]);

        float scaled_size_x = letter_data.size_x * raw_scale;
        float scaled_size_y = letter_data.size_y * raw_scale;

        array[(fpv * 0) + 0] = current_width;                       array[(fpv * 0) + 1] = scaled_size_y;
        array[(fpv * 1) + 0] = current_width;                       array[(fpv * 1) + 1] = 0.0f;
        array[(fpv * 2) + 0] = current_width + scaled_size_x;       array[(fpv * 2) + 1] = 0.0f;
        array[(fpv * 3) + 0] = current_width;                       array[(fpv * 3) + 1] = scaled_size_y;
        array[(fpv * 4) + 0] = current_width + scaled_size_x;       array[(fpv * 4) + 1] = 0.0f;
        array[(fpv * 5) + 0] = current_width + scaled_size_x;       array[(fpv * 5) + 1] = scaled_size_y;

        current_width += scaled_size_x;
    };

    for(unsigned int i=0; i<m_current_settings.text.size(); ++i)
        construct_character(i);
}

void Draw_Module__Text_Field::M_construct_colors(float* _colors, unsigned int _amount)
{
    for(unsigned int i=0; i<_amount; ++i)
        _colors[i] = 1.0f;
}

void Draw_Module__Text_Field::M_construct_texture_coords(float* _texture_coords, unsigned int _amount, unsigned int _amount_per_character)
{
//    L_ASSERT(texture().floats_per_vertex() > 1);    //  single-dimentional font is not supported :D

    for(unsigned int i=0; i<_amount; ++i)
        _texture_coords[i] = 0.0f;

//    unsigned int fpv = texture().floats_per_vertex();
    unsigned int fpv = 2;

    auto construct_character = [this, _texture_coords, _amount_per_character, fpv](unsigned int _character_index)
    {
        float* array = &(_texture_coords[_character_index * _amount_per_character]);

        const Letter_Data& letter_data = m_current_settings.font->get_letter_data(m_current_settings.text[_character_index]);

        array[(fpv * 0) + 0] = letter_data.pos_x;                           array[(fpv * 0) + 1] = letter_data.pos_y + letter_data.size_y;
        array[(fpv * 1) + 0] = letter_data.pos_x;                           array[(fpv * 1) + 1] = letter_data.pos_y;
        array[(fpv * 2) + 0] = letter_data.pos_x + letter_data.size_x;      array[(fpv * 2) + 1] = letter_data.pos_y;
        array[(fpv * 3) + 0] = letter_data.pos_x;                           array[(fpv * 3) + 1] = letter_data.pos_y + letter_data.size_y;
        array[(fpv * 4) + 0] = letter_data.pos_x + letter_data.size_x;      array[(fpv * 4) + 1] = letter_data.pos_y;
        array[(fpv * 5) + 0] = letter_data.pos_x + letter_data.size_x;      array[(fpv * 5) + 1] = letter_data.pos_y + letter_data.size_y;
    };

    for(unsigned int i=0; i<m_current_settings.text.size(); ++i)
        construct_character(i);
}


void Draw_Module__Text_Field::M_reconfigure()
{
    m_current_settings = m_configurable_settings;

    if(m_configurable_settings.text.size() == 0)
        return;

    texture().set_picture(m_current_settings.font->picture());

    const unsigned int coords_per_character = 3 * 6;            //  theese magic numbers should be taken from shader
    const unsigned int colors_per_character = 4 * 6;
    const unsigned int texture_coords_per_character = 2 * 6;

    unsigned int coords_amount = coords_per_character * m_current_settings.text.size();
    unsigned int colors_amount = colors_per_character * m_current_settings.text.size();
    unsigned int texture_coords_amount = texture_coords_per_character * m_current_settings.text.size();

    float* coords_buffer = new float[coords_amount];
    float* colors_buffer = new float[colors_amount];
    float* texture_coords_buffer = new float[texture_coords_amount];

    M_construct_coords(coords_buffer, coords_amount, coords_per_character);
    M_construct_colors(colors_buffer, colors_amount);
    M_construct_texture_coords(texture_coords_buffer, texture_coords_amount, texture_coords_per_character);

    vertices().use_array(coords_buffer, coords_amount);
    colors().use_array(colors_buffer, colors_amount);
    texture().use_array(texture_coords_buffer, texture_coords_amount);
    texture().reconfigure_texture_coords();
}



void Draw_Module__Text_Field::update(float _dt)
{
    if(m_current_settings != m_configurable_settings)
        M_reconfigure();

    if(m_current_settings.text.size() == 0)
        return;

    Draw_Module_Base::update(_dt);
}






























































