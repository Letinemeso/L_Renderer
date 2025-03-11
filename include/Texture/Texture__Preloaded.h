#pragma once

#include <Resources_Manager.h>

#include <Texture/Texture.h>
#include <Resources/Picture.h>


namespace LR
{

    class Texture__Preloaded : public LR::Texture
    {
    public:
        INIT_VARIABLE(LR::Texture__Preloaded, LR::Texture)

    private:
        const Picture* m_picture = nullptr;

    public:
        inline const Picture* picture() const { return m_picture; }

    public:
        void set_picture(const Picture* _picture);

    };


    class Texture_Stub__Preloaded : public LR::Texture_Stub
    {
    public:
        INIT_VARIABLE(LR::Texture_Stub__Preloaded, LR::Texture_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, picture_name)
        FIELDS_END

    public:
        const LEti::Resources_Manager* resources_manager = nullptr;

    public:
        std::string picture_name;

    public:
        INIT_BUILDER_STUB(Texture__Preloaded)

    };

}
