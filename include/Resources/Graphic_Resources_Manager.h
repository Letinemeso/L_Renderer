#pragma once

#include <L_Debug/L_Debug.h>
#include <Data_Structures/Map.h>
#include <Stuff/Function_Wrapper.h>

#include <Variable_Base.h>
#include <Builder_Stub.h>


namespace LR
{

    class Graphic_Resources_Manager : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Graphic_Resources_Manager, LV::Variable_Base)

    public:
        using Resources_Map = LDS::Map<std::string, LV::Variable_Base*>;

    private:
        Resources_Map m_resources;

    public:
        Graphic_Resources_Manager();
        ~Graphic_Resources_Manager();

        Graphic_Resources_Manager(const Graphic_Resources_Manager&) = delete;
        Graphic_Resources_Manager(Graphic_Resources_Manager&&) = delete;

    public:
        //  Manager WILL delete added objects on clear / manager destruction
        void add_resource(const std::string& _name, LV::Variable_Base* _resource, bool _rewrite = false);
        void remove_resource(const std::string& _name);

        void clear();

    public:
        template<typename Resource_Type>
        const Resource_Type* get_resource(const std::string& _name) const;

    };

    template<typename Resource_Type>
    const Resource_Type* Graphic_Resources_Manager::get_resource(const std::string& _name) const
    {
        Resources_Map::Const_Iterator maybe_resource_it = m_resources.find(_name);
        L_ASSERT(maybe_resource_it.is_ok());

        Resource_Type* result = LV::cast_variable<Resource_Type>(*maybe_resource_it);
        L_ASSERT(result);

        return result;
    }



    class Graphic_Resources_Manager_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Graphic_Resources_Manager_Stub, LV::Builder_Stub)

        INIT_CHILDS_LISTS
        ADD_CHILDS_LIST("*", &resources_stubs)
        CHILDS_LISTS_END

    public:
        LV::Variable_Base::Childs_List resources_stubs;

    public:
        ~Graphic_Resources_Manager_Stub();

    protected:
        INIT_BUILDER_STUB(Graphic_Resources_Manager)

    };

}
