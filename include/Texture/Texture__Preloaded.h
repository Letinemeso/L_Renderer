#pragma once

#include <Resources_Manager.h>

#include <Texture/Texture.h>
#include <Texture/Texture__Default.h>


namespace LR
{

    class Texture__Preloaded : public Texture
    {
    public:
        INIT_VARIABLE(LR::Texture__Preloaded, LR::Texture)

    private:
        Texture__Default* m_texture = nullptr;

    public:
        inline void set_texture(Texture__Default* _ptr) { m_texture = _ptr; }       //  does NOT take ownership

    public:
        void prepare_to_draw() override;

    };


    class Texture_Stub__Preloaded : public Texture_Stub
    {
    public:
        INIT_VARIABLE(LR::Texture_Stub__Preloaded, LR::Texture_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, texture_resource_name)
        FIELDS_END

    public:
        LST::Function<const LEti::Resources_Manager*()> resources_manager_getter;

    public:
        std::string texture_resource_name;

    public:
        INIT_BUILDER_STUB(Texture__Preloaded)

    };

}
