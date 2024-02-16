#include "Picture/Graphic_Resources_Manager.h"


using namespace LR;


Graphic_Resources_Manager::Graphic_Resources_Manager()
{

}

Graphic_Resources_Manager::~Graphic_Resources_Manager()
{
    clear();
}



void Graphic_Resources_Manager::M_try_to_load_resources_type(const LV::MDL_Variable_Stub& _stub, const LST::Function<void(const std::string&, const std::string&)>& _load_func)
{
    for(LDS::Map<std::string, LV::MDL_Variable_Stub>::Const_Iterator it = _stub.childs.iterator(); !it.end_reached(); ++it)
    {
        const LV::MDL_Variable_Stub& stub = *it;

        LDS::Map<std::string, LDS::Vector<std::string>>::Const_Iterator path_field = stub.fields.find("path");
        L_ASSERT(!path_field.end_reached());
        L_ASSERT(path_field->size() == 1);

        _load_func(it.key(), (*path_field)[0]);
    }
}



void Graphic_Resources_Manager::load_picture(const std::string& _name, const std::string& _path, bool _rewrite)
{
    Picture* picture = LR::load_picture(_path);
    L_ASSERT(picture);

    add_picture(_name, picture, _rewrite);
}

void Graphic_Resources_Manager::load_font(const std::string& _name, const std::string& _path, bool _rewrite)
{
    Font* font = LR::load_font(_path);
    L_ASSERT(font);

    add_font(_name, font, _rewrite);
}

void Graphic_Resources_Manager::load_resources(const LV::MDL_Variable_Stub& _stub, bool _rewrite)
{
    LST::Function<void(const std::string&, const std::string&)> picture_load_func = [this, _rewrite](const std::string& _name, const std::string& _path)
    {
        load_picture(_name, _path, _rewrite);
    };
    LST::Function<void(const std::string&, const std::string&)> font_load_func = [this, _rewrite](const std::string& _name, const std::string& _path)
    {
        load_font(_name, _path, _rewrite);
    };

    LDS::Map<std::string, LV::MDL_Variable_Stub>::Const_Iterator stub_it = _stub.childs.find("pictures");
    if(!stub_it.end_reached())
        M_try_to_load_resources_type(*stub_it, picture_load_func);

    stub_it = _stub.childs.find("fonts");
    if(!stub_it.end_reached())
        M_try_to_load_resources_type(*stub_it, font_load_func);
}

void Graphic_Resources_Manager::clear()
{
    for(LDS::Map<std::string, Picture*>::Iterator it = m_pictures.iterator(); !it.end_reached(); ++it)
        delete *it;
    for(LDS::Map<std::string, Font*>::Iterator it = m_fonts.iterator(); !it.end_reached(); ++it)
        delete *it;

    m_pictures.clear();
    m_fonts.clear();
}



void Graphic_Resources_Manager::add_picture(const std::string& _name, Picture* _picture, bool _rewrite)
{
    L_ASSERT(_picture);

    LDS::Map<std::string, Picture*>::Iterator maybe_loaded_picture = m_pictures.find(_name);
    if(maybe_loaded_picture.end_reached())
    {
        m_pictures.insert(_name, _picture);
        return;
    }

    L_ASSERT(_rewrite);     //  if rewrite is not allowed, program should crash if image with same name already loaded

    delete *maybe_loaded_picture;
    *maybe_loaded_picture = _picture;
}

void Graphic_Resources_Manager::remove_picture(const std::string& _name)
{
    LDS::Map<std::string, Picture*>::Iterator maybe_loaded_picture = m_pictures.find(_name);
    L_ASSERT(!maybe_loaded_picture.end_reached());

    delete *maybe_loaded_picture;
    m_pictures.erase(maybe_loaded_picture);
}

void Graphic_Resources_Manager::add_font(const std::string& _name, Font* _font, bool _rewrite)
{
    L_ASSERT(_font);

    LDS::Map<std::string, Font*>::Iterator maybe_loaded_picture = m_fonts.find(_name);
    if(maybe_loaded_picture.end_reached())
    {
        m_fonts.insert(_name, _font);
        return;
    }

    L_ASSERT(_rewrite);     //  if rewrite is not allowed, program should crash if font with same name already loaded

    delete *maybe_loaded_picture;
    *maybe_loaded_picture = _font;
}

void Graphic_Resources_Manager::remove_font(const std::string& _name)
{
    LDS::Map<std::string, Font*>::Iterator maybe_loaded_font = m_fonts.find(_name);
    L_ASSERT(!maybe_loaded_font.end_reached());

    delete *maybe_loaded_font;
    m_fonts.erase(maybe_loaded_font);
}



const Picture* Graphic_Resources_Manager::get_picture(const std::string& _name) const
{
    LDS::Map<std::string, Picture*>::Const_Iterator maybe_loaded_picture = m_pictures.find(_name);

    if(maybe_loaded_picture.end_reached())
        return nullptr;

    return *maybe_loaded_picture;
}

const Font* Graphic_Resources_Manager::get_font(const std::string& _name) const
{
    LDS::Map<std::string, Font*>::Const_Iterator maybe_loaded_font = m_fonts.find(_name);

    if(maybe_loaded_font.end_reached())
        return nullptr;

    return *maybe_loaded_font;
}
