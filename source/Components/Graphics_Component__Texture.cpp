#include <Components/Graphics_Component__Texture.h>

using namespace LR;


INIT_FIELDS(LR::Graphics_Component__Texture, LR::Graphics_Component)
FIELDS_END


Graphics_Component__Texture::Graphics_Component__Texture()
{

}


Graphics_Component__Texture::~Graphics_Component__Texture()
{
    glDeleteTextures(1, &m_texture_object);
}



void Graphics_Component__Texture::set_picture(const Picture* _picture)
{
    glDeleteTextures(1, &m_texture_object);

    m_picture = _picture;

    glGenTextures(1, &m_texture_object);
    glBindTexture(GL_TEXTURE_2D, m_texture_object);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_picture->width(), m_picture->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_picture->data());
}

void Graphics_Component__Texture::reconfigure_texture_coords()
{
    L_ASSERT(m_picture);
    L_ASSERT(m_buffer.size() > 0);

    for(unsigned int i=0; i<m_buffer.size(); i += 2)
    {
        glm::vec2 vertex;
        vertex.x = m_buffer[i];
        vertex.y = m_buffer[i + 1];
        m_picture->convert_texture_coords_vertex(vertex);
        m_buffer[i] = vertex.x;
        m_buffer[i + 1] = vertex.y;
    }
}



void Graphics_Component__Texture::prepare() const
{
    Graphics_Component::prepare();

    L_ASSERT(m_texture_object);

    glBindTexture(GL_TEXTURE_2D, m_texture_object);
}





INIT_FIELDS(LR::Graphics_Component_Stub__Texture, LR::Graphics_Component_Stub)

ADD_FIELD(std::string, picture_name)
ADD_FIELD(bool, texture_coords_in_pixels)

FIELDS_END


LV::Variable_Base* Graphics_Component_Stub__Texture::M_construct_product() const
{
    return new Graphics_Component__Texture;
}

void Graphics_Component_Stub__Texture::M_init_constructed_product(LV::Variable_Base* _product) const
{
    Graphics_Component_Stub::M_init_constructed_product(_product);

    Graphics_Component__Texture* product = (Graphics_Component__Texture*)_product;

    L_ASSERT(data);
    L_ASSERT(data_size > 0);
    L_ASSERT(floats_per_vertex > 0);

    product->buffer().free_memory();
    product->buffer().allocate_memory(data_size);
    product->buffer().copy_array(data, data_size);
    product->buffer().setup_buffer(attribute_index, floats_per_vertex);

    L_ASSERT(resources_manager);

    const Picture* picture = resources_manager->get_picture(picture_name);

    L_ASSERT(picture);

    product->set_picture(picture);

    if(texture_coords_in_pixels)
        product->reconfigure_texture_coords();
}
