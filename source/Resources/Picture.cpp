#include <Resources/Picture.h>

#include <stb_image.h>

using namespace LR;


Picture::Picture()
{

}

Picture::~Picture()
{
    stbi_image_free(m_picture_data);
}



void Picture::convert_texture_coords_vertex(glm::vec2 &_vertex) const
{
    _vertex.x = _vertex.x / m_width;
    _vertex.y = _vertex.y / m_height;
}





BUILDER_STUB_CONSTRUCTION_FUNC(Picture_Stub) BUILDER_STUB_CONSTRUCTION_FUNC_DEFAULT_IMPL

BUILDER_STUB_INITIALIZATION_FUNC(Picture_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    L_ASSERT(image_file_path.size() > 0);

    stbi_set_flip_vertically_on_load(true);

    int width, height;
    unsigned char* picture_data = stbi_load(image_file_path.c_str(), &width, &height, nullptr, 4);
    L_ASSERT(picture_data);

    product->m_picture_data = picture_data;
    product->m_width = width;
    product->m_height = height;
}
