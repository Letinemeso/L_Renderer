#pragma once

#include <vec2.hpp>
#include <vec4.hpp>

#include <L_Debug/L_Debug.h>

#include <Variable_Base.h>
#include <Builder_Stub.h>


namespace LR
{

    class Picture : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LR::Picture, LV::Variable_Base)

    private:
        friend class Picture_Stub;

    public:
        using Const_Pixel = const unsigned char*;
        using Pixel = unsigned char*;

    private:
        unsigned int m_width = 0;
        unsigned int m_height = 0;
        unsigned int m_channels = 0;

        unsigned int m_buffer_size = 0;
        unsigned char* m_picture_data = nullptr;

    public:
        Picture(const Picture&) = delete;
        Picture(Picture&&) = delete;

    protected:
        Picture();

    public:
        Picture(unsigned int _width, unsigned int _height, bool _has_alpha);
        ~Picture();

    public:
        inline unsigned int width() const { return m_width; }
        inline unsigned int height() const { return m_height; }
        inline unsigned int channels() const { return m_channels; }
        inline const unsigned char* data() const { return m_picture_data; }
        inline Pixel pixel(unsigned int _x, unsigned int _y) { return m_picture_data + ((m_width * m_channels * _y) + (m_channels * _x)); }
        inline Const_Pixel pixel(unsigned int _x, unsigned int _y) const { return m_picture_data + ((m_width * m_channels * _y) + (m_channels * _x)); }

    public:
        void convert_texture_coords_vertex(glm::vec2& _vertex) const;

    public:
        void color_pixel(unsigned int _x, unsigned int _y, const unsigned char* _color);
        void fill_square_with_color(unsigned int _x, unsigned int _y, unsigned int _width, unsigned int _height, const unsigned char* _color);
        void replace_with_picture(unsigned int _x, unsigned int _y, const Picture* _picture, const glm::vec4& _color_multipliers = {1.0f, 1.0f, 1.0f, 1.0f}, unsigned int _offset_for_picture_x = 0, unsigned int _offset_for_picture_y = 0, unsigned int _picture_size_x = 0xFFFFFFFF, unsigned int _picture_size_y = 0xFFFFFFFF);

    };


    class Picture_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LR::Picture_Stub, LV::Builder_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, image_file_path)
        FIELDS_END

    public:
        std::string image_file_path;

    protected:
        INIT_BUILDER_STUB(Picture)

    };

}
