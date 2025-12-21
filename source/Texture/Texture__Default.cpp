#include <Texture/Texture__Default.h>

#include <glew.h>

#include <Binds_Controller/Binds_Controller.h>

using namespace LR;


Texture__Default::Settings::Settings()
{
    min_filter = GL_NEAREST;
    mag_filter = GL_NEAREST;
    wrap_s = GL_REPEAT;
    wrap_t = GL_REPEAT;
}





Texture__Default::Texture__Default()
{
    glGenTextures(1, &m_texture_object);
}

Texture__Default::~Texture__Default()
{
    L_ASSERT(glIsTexture(m_texture_object));
    glDeleteTextures(1, &m_texture_object);
}



void Texture__Default::set_settings(const Settings& _settings)
{
    m_current_settings = _settings;

    LR::Binds_Controller::instance().bind_texture(m_bind_index, m_texture_object);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _settings.min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _settings.mag_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _settings.wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _settings.wrap_t);
}

void Texture__Default::set_bind_index(unsigned int _index)
{
    L_DEBUG_FUNC_NOARG([&]()
                       {
                           int textures_amount = 0;
                           glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textures_amount);

                           L_ASSERT(_index < textures_amount);
                       });

    m_bind_index = _index;
}



void Texture__Default::create_from_picture(const Picture* _picture)
{
    L_ASSERT(_picture);

    m_width = _picture->width();
    m_height = _picture->height();

    LR::Binds_Controller::instance().bind_texture(bind_index(), opengl_texture_object());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _picture->data());
}

void Texture__Default::set_picture(const Picture *_picture)
{
    L_ASSERT(_picture);

    m_picture = _picture;
    create_from_picture(m_picture);
}



void Texture__Default::prepare_to_draw()
{
    LR::Binds_Controller::instance().bind_texture(m_bind_index, m_texture_object);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Texture_Stub__Default)

BUILDER_STUB_INITIALIZATION_FUNC(Texture_Stub__Default)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_bind_index(bind_index);

    apply_settings(product);

    if(picture)
    {
        L_ASSERT(picture_name.size() == 0);
        product->create_from_picture(picture);
        return;
    }

    if(picture_name.size() == 0)
        return;

    L_ASSERT(resources_manager_getter);
    const LEti::Resources_Manager* resources_manager = resources_manager_getter();
    L_ASSERT(resources_manager);

    product->set_picture(resources_manager->get_resource<Picture>(picture_name));
}



ON_VALUES_ASSIGNED_IMPLEMENTATION(Texture_Stub__Default)
{
    if(!picture_stub)
        return;

    L_ASSERT(picture_name.size() == 0);

    picture = LR::Picture_Stub::construct_from(picture_stub);
}



void Texture_Stub__Default::apply_settings(Texture__Default* _product) const
{
    Texture__Default::Settings result;

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
        result.wrap_s = GL_REPEAT;
    else if(wrap_s == "Clamp_To_Edge")
        result.wrap_s = GL_CLAMP_TO_EDGE;
    else
    {
        L_ASSERT(false);    //  haven't used any other type yet, so just add them here if needed
    }

    if(wrap_t == "Repeat")
        result.wrap_t = GL_REPEAT;
    else if(wrap_t == "Clamp_To_Edge")
        result.wrap_t = GL_CLAMP_TO_EDGE;
    else
    {
        L_ASSERT(false);    //  haven't used any other type yet, so just add them here if needed
    }

    _product->set_settings(result);
}



Texture_Stub__Default::~Texture_Stub__Default()
{
    delete picture_stub;
    delete picture;
}
