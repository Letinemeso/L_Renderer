#include <Components/Graphics_Component__Texture.h>

using namespace LR;


Graphics_Component__Texture::Graphics_Component__Texture()
{

}


Graphics_Component__Texture::~Graphics_Component__Texture()
{
    glDeleteTextures(1, &m_texture_object);
}



void Graphics_Component__Texture::set_picture(const Picture* _picture, const Texture_Settings& _settings)
{
    glDeleteTextures(1, &m_texture_object);

    m_picture = _picture;

    glGenTextures(1, &m_texture_object);
    glBindTexture(GL_TEXTURE_2D, m_texture_object);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _settings.min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _settings.mag_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _settings.wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _settings.wrap_t);
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



void Graphics_Component__Texture::update(float _dt) const
{
    Graphics_Component::update(_dt);
}

void Graphics_Component__Texture::prepare_to_draw() const
{
    Parent_Type::prepare_to_draw();

    L_ASSERT(m_texture_object);

    glBindTexture(GL_TEXTURE_2D, m_texture_object);
}





LV::Variable_Base* Graphics_Component_Stub__Texture::M_construct_product() const
{
    return new Graphics_Component__Texture;
}

void Graphics_Component_Stub__Texture::M_init_constructed_product(LV::Variable_Base* _product) const
{
    Graphics_Component_Stub::M_init_constructed_product(_product);

    Graphics_Component__Texture* product = (Graphics_Component__Texture*)_product;

    L_ASSERT(resources_manager);

    product->inject_resources_manager(resources_manager);

    if(picture_name.size() == 0)
        return;

    const Picture* picture = resources_manager->get_resource<Picture>(picture_name);

    L_ASSERT(picture);

    product->set_picture(picture);

    if(data == nullptr || data_size == 0)
        return;

    if(texture_coords_in_pixels)
        product->reconfigure_texture_coords();
}
