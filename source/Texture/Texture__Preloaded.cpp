#include <Texture/Texture__Preloaded.h>

using namespace LR;


void Texture__Preloaded::set_picture(const Picture *_picture)
{
    m_picture = _picture;

    m_width = m_picture->width();
    m_height = m_picture->height();

    glBindTexture(GL_TEXTURE_2D, opengl_texture_object());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_picture->data());
}




BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Texture_Stub__Preloaded)

BUILDER_STUB_INITIALIZATION_FUNC(Texture_Stub__Preloaded)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    L_ASSERT(resources_manager);

    if(picture_name.size() == 0)
        return;

    product->set_picture(resources_manager->get_resource<Picture>(picture_name));
}
