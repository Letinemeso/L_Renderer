#pragma once

#include <glew.h>

#include "Draw_Modules/Draw_Module_Base.h"


namespace LR
{

    class Default_Draw_Module : public Draw_Module_Base
    {
    public:
        DECLARE_VARIABLE;

    private:
        const LR::Shader_Transform_Component* m_shader_transform_component = nullptr;

    public:
        Default_Draw_Module();
        ~Default_Draw_Module();

    protected:
        LR::Texture m_texture;      //  TODO: this stuff should be added in Draw_Module_Base like components
        LR::Vertices m_vertices;
        LR::Colors m_colors;

    public:
        inline void set_shader_transform_component(const LR::Shader_Transform_Component* _ptr) { m_shader_transform_component = _ptr; }

    public:
        inline LR::Texture& texture() { return m_texture; }
        inline LR::Vertices& vertices() { return m_vertices; }
        inline LR::Colors& colors() { return m_colors; }
        inline const LR::Texture& texture() const { return m_texture; }
        inline const LR::Vertices& vertices() const { return m_vertices; }
        inline const LR::Colors& colors() const { return m_colors; }

    public:
        void init_vertices(const float* const _coords, unsigned int _coords_count);
        void init_colors(const float* const _colors, unsigned int _colors_count);
        void init_texture(const Picture* _picture, const float* const tex_coords, unsigned int _tex_coords_count);

        void set_texture(const Picture* _picture);
        void set_texture_coords(const float* _tc, unsigned int _tc_count);

        void move_raw(const glm::vec3& _stride);

    protected:
        void M_draw() override;

    public:
        void update(float _dt) override;

    };

    class Default_Draw_Module_Stub : public Draw_Module_Base_Stub
    {
    public:
        DECLARE_VARIABLE;

    public:
        const LR::Graphic_Resources_Manager* graphic_resources_manager = nullptr;
        const LR::Shader_Transform_Component* shader_transform_component = nullptr;

    public:
        std::string texture_name;

        unsigned int tcoords_count = 0;
        float* tcoords = nullptr;

        unsigned int coords_count = 0;
        float* coords = nullptr;

        unsigned int colors_count = 0;
        float* colors = nullptr;

    protected:
        LV::Variable_Base* M_construct_product() const override;
        void M_init_constructed_product(LV::Variable_Base* /*_product*/) const override;

    public:
        virtual ~Default_Draw_Module_Stub();

    };

}
