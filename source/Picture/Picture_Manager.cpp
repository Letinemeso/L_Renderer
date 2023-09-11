#include "Picture/Picture_Manager.h"


using namespace LR;


Graphic_Resources_Manager::Graphic_Resources_Manager()
{

}

Graphic_Resources_Manager::~Graphic_Resources_Manager()
{
    clear();
}



void Graphic_Resources_Manager::load_resources(const LV::MDL_Variable_Stub& _stub, bool _rewrite)
{
    for(LDS::Map<std::string, LV::MDL_Variable_Stub>::Const_Iterator it = _stub.childs.iterator(); !it.end_reached(); ++it)
    {
        const LV::MDL_Variable_Stub& stub = *it;

        LDS::Map<std::string, LDS::Vector<std::string>>::Const_Iterator path_field = stub.fields.find("path");
        L_ASSERT(!path_field.end_reached());
        L_ASSERT(path_field->size() == 1);

        std::string name = it.key();
        std::string path = (*path_field)[0];

        Picture* picture = load_picture(path);
        L_ASSERT(picture);

        LDS::Map<std::string, Picture*>::Iterator maybe_loaded_picture = m_pictures.find(name);
        if(maybe_loaded_picture.end_reached())
        {
            m_pictures.insert((std::string&&)name, picture);
            continue;
        }

        L_ASSERT(_rewrite);     //  if rewrite is not allowed, program should crash if image with same name already loaded

        delete *maybe_loaded_picture;
        *maybe_loaded_picture = picture;
    }
}

void Graphic_Resources_Manager::clear()
{
    for(LDS::Map<std::string, Picture*>::Iterator it = m_pictures.iterator(); !it.end_reached(); ++it)
        delete *it;

    m_pictures.clear();
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



const Picture* Graphic_Resources_Manager::get_picture(const std::string& _name) const
{
    LDS::Map<std::string, Picture*>::Const_Iterator maybe_loaded_picture = m_pictures.find(_name);

    if(maybe_loaded_picture.end_reached())
        return nullptr;

    return *maybe_loaded_picture;
}
