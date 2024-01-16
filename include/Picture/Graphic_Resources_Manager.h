#pragma once

#include <L_Debug/L_Debug.h>
#include <Data_Structures/Map.h>
#include <Stuff/Function_Wrapper.h>

#include <Variable_Base.h>

#include <Picture/Picture.h>
#include <Picture/Font.h>


namespace LR
{

    class Graphic_Resources_Manager
    {
    private:
        LDS::Map<std::string, Picture*> m_pictures;
        LDS::Map<std::string, Font*> m_fonts;

    public:
        Graphic_Resources_Manager();
        ~Graphic_Resources_Manager();

        Graphic_Resources_Manager(const Graphic_Resources_Manager&) = delete;
        Graphic_Resources_Manager(Graphic_Resources_Manager&&) = delete;

    private:
        void M_try_to_load_resources_type(const LV::MDL_Variable_Stub& _stub, const LST::Function<void(const std::string&, const std::string&)>& _load_func);

    public:
        void load_picture(const std::string& _name, const std::string& _path, bool _rewrite = false);
        void load_font(const std::string& _name, const std::string& _path, bool _rewrite = false);
        void load_resources(const LV::MDL_Variable_Stub& _stub, bool _rewrite = false);
        void clear();

    public:
        //  Manager WILL delete added objects on clear / manager destruction
        void add_picture(const std::string& _name, Picture* _picture, bool _rewrite = false);
        void remove_picture(const std::string& _name);
        void add_font(const std::string& _name, Font* _font, bool _rewrite = false);
        void remove_font(const std::string& _name);

    public:
        const Picture* get_picture(const std::string& _name) const;
        const Font* get_font(const std::string& _name) const;

    };

}
