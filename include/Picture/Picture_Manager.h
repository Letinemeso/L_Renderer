#ifndef PICTURE_MANAGER_H
#define PICTURE_MANAGER_H

#include <Data_Structures/Map.h>

#include <Variable_Base.h>

#include <L_Debug/L_Debug.h>

#include <Picture/Picture.h>


namespace LR
{

    class Graphic_Resources_Manager
	{
    private:
        LDS::Map<std::string, Picture*> m_pictures;

    public:
        Graphic_Resources_Manager();
        ~Graphic_Resources_Manager();

        Graphic_Resources_Manager(const Graphic_Resources_Manager&) = delete;
        Graphic_Resources_Manager(Graphic_Resources_Manager&&) = delete;

    public:
        void load_resources(const LV::MDL_Variable_Stub& _stub, bool _rewrite = false);
        void clear();

    public:
        void add_picture(const std::string& _name, Picture* _picture, bool _rewrite = false);   //  Manager WILL delete added image object on clear / manager object destruction
        void remove_picture(const std::string& _name);

    public:
        const Picture* get_picture(const std::string& _name) const;

    };

}

#endif // PICTURE_MANAGER_H
