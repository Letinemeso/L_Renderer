#include <Components/Graphics_Component__Texture.h>

using namespace LR;


Graphics_Component__Texture::Graphics_Component__Texture()
{

}


Graphics_Component__Texture::~Graphics_Component__Texture()
{
    if(m_owns_texture)
        delete m_texture;
}



void Graphics_Component__Texture::set_texture(Texture *_texture, bool _take_ownership)
{
    if(m_owns_texture)
        delete m_texture;

    m_texture = _texture;
    m_owns_texture = _take_ownership;
}

void Graphics_Component__Texture::remove_texture()
{
    if(m_owns_texture)
        delete m_texture;

    m_texture = nullptr;
}

Texture* Graphics_Component__Texture::extract_texture()
{
    Texture* result = m_texture;
    m_texture = nullptr;
    return result;
}



void Graphics_Component__Texture::reconfigure_texture_coords()
{
    L_ASSERT(m_texture);
    L_ASSERT(m_buffer.size() > 0);
    L_ASSERT(m_buffer.floats_per_vertex() >= 2);

    Buffer::Element_Modification_Func modification_func = [this](float& _element, unsigned int _index)
    {
        float* elements_as_array = &_element;
        elements_as_array[0] /= m_texture->width();
        elements_as_array[1] /= m_texture->height();
    };

    m_buffer.modify_buffer(modification_func, 0, Buffer::All_Elements, m_buffer.floats_per_vertex());
}



void Graphics_Component__Texture::prepare_to_draw() const
{
    Parent_Type::prepare_to_draw();

    L_ASSERT(m_texture);
    m_texture->prepare_to_draw();
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Graphics_Component_Stub__Texture)

BUILDER_STUB_INITIALIZATION_FUNC(Graphics_Component_Stub__Texture)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    if(texture_stub)
        product->set_texture(Texture_Stub::construct_from(texture_stub));

    if(texture_stub && data.size() > 0 && texture_coords_in_pixels)
        product->reconfigure_texture_coords();
}



Graphics_Component_Stub__Texture::~Graphics_Component_Stub__Texture()
{
    delete texture_stub;
}
