#pragma once

#include <L_Debug/L_Debug.h>

#include <Components/Graphics_Component__Default.h>
#include <Texture/Texture.h>

namespace LR
{

    class Graphics_Component__Texture final : public Graphics_Component__Default
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component__Texture, LR::Graphics_Component__Default)

    public:
        Texture* m_texture = nullptr;
        bool m_owns_texture = true;

    public:
        Graphics_Component__Texture();
        ~Graphics_Component__Texture();

    public:
        inline Texture* texture() { return m_texture; }
        inline const Texture* texture() const { return m_texture; }

    public:
        void set_texture(Texture* _texture, bool _take_ownership = true);
        void remove_texture();                          //  nullifies texture and deletes it if has ownership
        [[nodiscard]] Texture* extract_texture();       //  returns texture and hands over ownership

    public:
        void reconfigure_texture_coords();

    public:
        void prepare_to_draw() const override;

    };


    class Graphics_Component_Stub__Texture : public Graphics_Component_Stub__Default
    {
    public:
        INIT_VARIABLE(LR::Graphics_Component_Stub__Texture, LR::Graphics_Component_Stub__Default)

        INIT_FIELDS
        ADD_FIELD(bool, texture_coords_in_pixels)
        FIELDS_END

        INIT_CHILDS
        ADD_CHILD("texture_stub", texture_stub)
        CHILDS_END

    public:
        bool texture_coords_in_pixels = true;

        Texture_Stub* texture_stub = nullptr;

    public:
        INIT_BUILDER_STUB(Graphics_Component__Texture)

    public:
        ~Graphics_Component_Stub__Texture();

    };

}
