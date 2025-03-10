#include <Components/Graphics_Component__Texture.h>

using namespace LR;


Graphics_Component__Texture::Graphics_Component__Texture()
{

}


Graphics_Component__Texture::~Graphics_Component__Texture()
{
    glDeleteTextures(1, &m_texture_object);
}



void Graphics_Component__Texture::set_texture_bind_index(unsigned int _value)
{
    m_texture_bind_index = GL_TEXTURE0 + _value;
    L_ASSERT(m_texture_bind_index < GL_MAX_TEXTURE_UNITS);
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

    Buffer::Element_Modification_Func modification_func = [this](float& _element, unsigned int _index)
    {
        unsigned int component_index = _index % m_buffer.floats_per_vertex();
        if(component_index == 0)
            _element /= m_picture->width();
        else if(component_index == 1)
            _element /= m_picture->height();
    };

    m_buffer.modify_buffer(modification_func);
}



void Graphics_Component__Texture::update(float _dt) const
{
    Graphics_Component::update(_dt);
}

void Graphics_Component__Texture::prepare_to_draw() const
{
    Parent_Type::prepare_to_draw();

    L_ASSERT(m_texture_object);

    glActiveTexture(m_texture_bind_index);
    glBindTexture(GL_TEXTURE_2D, m_texture_object);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Graphics_Component_Stub__Texture)

BUILDER_STUB_INITIALIZATION_FUNC(Graphics_Component_Stub__Texture)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_texture_bind_index(texture_bind_index);

    L_ASSERT(resources_manager);
    product->inject_resources_manager(resources_manager);

    if(picture_name.size() == 0)
        return;

    const Picture* picture = resources_manager->get_resource<Picture>(picture_name);
    L_ASSERT(picture);
    Graphics_Component__Texture::Texture_Settings settings = M_parse_settings();

    product->set_picture(picture, settings);

    if(data.size() == 0)
        return;

    if(texture_coords_in_pixels)
        product->reconfigure_texture_coords();
}



Graphics_Component__Texture::Texture_Settings Graphics_Component_Stub__Texture::M_parse_settings() const
{
    Graphics_Component__Texture::Texture_Settings result;

    if(min_filter == "Nearest")
        result.min_filter = GL_NEAREST;
    else if(min_filter == "Linear")
        result.min_filter = GL_LINEAR;
    else
    {
        L_ASSERT(false);    //  haven't used any other type yet, so just add them here if needed
    }

    if(mag_filter == "Nearest")
        result.mag_filter = GL_NEAREST;
    else if(mag_filter == "Linear")
        result.mag_filter = GL_LINEAR;
    else
    {
        L_ASSERT(false);    //  haven't used any other type yet, so just add them here if needed
    }

    if(wrap_s == "Repeat")
        result.wrap_s = GL_CLAMP_TO_EDGE;
    else if(wrap_s == "Clamp_To_Edge")
        result.wrap_s = GL_REPEAT;
    else
    {
        L_ASSERT(false);    //  haven't used any other type yet, so just add them here if needed
    }

    if(wrap_t == "Repeat")
        result.wrap_t = GL_CLAMP_TO_EDGE;
    else if(wrap_t == "Clamp_To_Edge")
        result.wrap_t = GL_REPEAT;
    else
    {
        L_ASSERT(false);    //  haven't used any other type yet, so just add them here if needed
    }

    return result;
}
