#pragma once

#include <L_Debug/L_Debug.h>

#include <Components/Graphics_Component.h>
#include <Picture/Picture.h>
#include <Picture/Graphic_Resources_Manager.h>

namespace LR
{

    class Graphics_Component__Texture final : public Graphics_Component
    {
    public:
        DECLARE_VARIABLE;

    private:
        unsigned int m_texture_object = 0;
        const Picture* m_picture = nullptr;

    public:
        Graphics_Component__Texture();
        Graphics_Component__Texture(const Graphics_Component__Texture&) = delete;
        Graphics_Component__Texture(Graphics_Component__Texture&&) = delete;
        void operator=(const Graphics_Component__Texture&) = delete;
        void operator=(Graphics_Component__Texture&&) = delete;

        ~Graphics_Component__Texture();

    public:
        void set_picture(const Picture* _picture);
        void reconfigure_texture_coords();

    public:
        inline const Picture* get_picture() const { return m_picture; }

    public:
        void prepare() const override;

    };



    class Graphics_Component_Stub__Texture : public Graphics_Component_Stub
    {
    public:
        DECLARE_VARIABLE;

    public:
        const Graphic_Resources_Manager* resources_manager = nullptr;

    public:
        std::string picture_name;
        bool texture_coords_in_pixels = true;

    protected:
        LV::Variable_Base* M_construct_product() const override;
        void M_init_constructed_product(LV::Variable_Base* _product) const override;

    };

}
