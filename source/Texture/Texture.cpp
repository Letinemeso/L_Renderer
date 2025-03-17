#include <Texture/Texture.h>

#include <glew.h>

#include <Binds_Controller/Binds_Controller.h>

using namespace LR;


Texture::Settings::Settings()
{
    min_filter = GL_NEAREST;
    mag_filter = GL_NEAREST;
    wrap_s = GL_REPEAT;
    wrap_t = GL_REPEAT;
}





Texture::Texture()
{
    glGenTextures(1, &m_texture_object);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_texture_object);
}



void Texture::set_settings(const Settings& _settings)
{
    m_current_settings = _settings;

    LR::Binds_Controller::instance().bind_texture(m_bind_index, m_texture_object);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _settings.min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _settings.mag_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _settings.wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _settings.wrap_t);
}

void Texture::set_bind_index(unsigned int _index)
{
    L_DEBUG_FUNC_NOARG([&]()
    {
        int textures_amount = 0;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textures_amount);

        L_ASSERT(_index < textures_amount);
    });

    m_bind_index = _index;
}



void Texture::prepare_to_draw()
{
    LR::Binds_Controller::instance().bind_texture(m_bind_index, m_texture_object);
}




BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Texture_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Texture_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_bind_index(bind_index);

    apply_settings(product);
}



void Texture_Stub::apply_settings(Constructed_Type* _product) const
{
    Texture::Settings result;

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

    _product->set_settings(result);
}
