#pragma once

#include <vec2.hpp>

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

    private:
        int m_width = 0, m_height = 0;
        unsigned char* m_picture_data = nullptr;

    public:
        Picture(const Picture&) = delete;
        Picture(Picture&&) = delete;

    protected:
        Picture();

    public:
        ~Picture();

    public:
        inline int width() const { return m_width; }
        inline int height() const { return m_height; }
        inline const unsigned char* data() const { return m_picture_data; }

    public:
        void convert_texture_coords_vertex(glm::vec2& _vertex) const;

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
