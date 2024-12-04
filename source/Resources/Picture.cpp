#include <Resources/Picture.h>

#include <stb_image.h>

using namespace LR;


Picture::Picture()
{

}


Picture::Picture(unsigned int _width, unsigned int _height, bool _has_alpha)
{
    m_width = _width;
    m_height = _height;
    m_channels = _has_alpha ? 4 : 3;

    m_buffer_size = m_width * m_height * m_channels;
    m_picture_data = new unsigned char[m_buffer_size] { 0 };

    M_construct_grid_representation();
}

Picture::~Picture()
{
    delete[] m_picture_data;
}



void Picture::M_construct_grid_representation()
{
    if(m_picture_grid_representation)
    {
        for(unsigned int i = 0; i < m_height; ++i)
            delete m_picture_grid_representation[i];
        delete m_picture_grid_representation;
    }

    m_picture_grid_representation = new unsigned char**[m_width];
    for(unsigned int x = 0; x < m_width; ++x)
        m_picture_grid_representation[x] = new unsigned char*[m_height];

    unsigned int grid_elements_amount = m_width * m_height;
    for(unsigned int i = 0; i < grid_elements_amount; ++i)
    {
        unsigned int buffer_index = i * m_channels;
        unsigned int grid_x = i % m_width;
        unsigned int grid_y = i / m_width;

        m_picture_grid_representation[grid_x][grid_y] = m_picture_data + buffer_index;
    }
}



void Picture::convert_texture_coords_vertex(glm::vec2 &_vertex) const
{
    _vertex.x = _vertex.x / m_width;
    _vertex.y = _vertex.y / m_height;
}



void Picture::color_pixel(unsigned int _x, unsigned int _y, const unsigned char* _color)
{
    unsigned char* pixel_data = m_picture_grid_representation[_x][_y];

    for(unsigned int i=0; i<m_channels; ++i)
        pixel_data[i] = _color[i];
}

void Picture::fill_square_with_color(unsigned int _x, unsigned int _y, unsigned int _width, unsigned int _height, const unsigned char* _color)
{
    unsigned int horizontal_limit = _x + _width;
    unsigned int vertical_limit = _y + _height;

    L_ASSERT(horizontal_limit <= m_width);
    L_ASSERT(vertical_limit <= m_height);

    for(unsigned int x = _x; x < horizontal_limit; ++x)
    {
        for(unsigned int y = _y; y < vertical_limit; ++y)
            color_pixel(x, y, _color);
    }
}

void Picture::replace_with_picture(unsigned int _x, unsigned int _y, const Picture* _picture, unsigned int _offset_for_picture_x, unsigned int _offset_for_picture_y, unsigned int _picture_size_x, unsigned int _picture_size_y)
{
    L_ASSERT(_picture);
    L_ASSERT(m_channels == _picture->m_channels);

    if(_picture_size_x == 0xFFFFFFFF)
        _picture_size_x = _picture->m_width;
    if(_picture_size_y == 0xFFFFFFFF)
        _picture_size_y = _picture->m_height;

    L_ASSERT(_offset_for_picture_x + _picture_size_x <= _picture->m_width);
    L_ASSERT(_offset_for_picture_y + _picture_size_y <= _picture->m_height);
    L_ASSERT(_x + _picture_size_x <= m_width);
    L_ASSERT(_y + _picture_size_y <= m_height);

    for(unsigned int x = 0; x < _picture_size_x; ++x)
    {
        for(unsigned int y = 0; y < _picture_size_y; ++y)
            color_pixel(x + _x, y + _y, _picture->pixel(x + _offset_for_picture_x, y + _offset_for_picture_y));
    }
}





BUILDER_STUB_CONSTRUCTION_FUNC(Picture_Stub) BUILDER_STUB_CONSTRUCTION_FUNC_DEFAULT_IMPL

BUILDER_STUB_INITIALIZATION_FUNC(Picture_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    L_ASSERT(image_file_path.size() > 0);

    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;
    unsigned char* picture_data = stbi_load(image_file_path.c_str(), &width, &height, &channels, 4);
    L_ASSERT(picture_data);

    product->m_width = width;
    product->m_height = height;
    product->m_channels = channels;

    product->m_buffer_size = width * height * channels;
    product->m_picture_data = picture_data;

    product->M_construct_grid_representation();
}
