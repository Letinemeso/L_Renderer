#ifndef __PICTURE
#define __PICTURE

#include <gtx/transform.hpp>

#include <L_Debug/L_Debug.h>


namespace LR
{

    class Picture
    {
    private:
        int m_width = 0, m_height = 0;
        unsigned char* m_picture_data = nullptr;

    private:
        Picture() {}
        friend Picture* load_picture(const std::string& _path);

    public:
        Picture(const Picture&) = delete;
        Picture(Picture&&) = delete;

    public:
        ~Picture();

    public:
        int width() const;
        int height() const;
        const unsigned char* data() const;

    public:
        void convert_texture_coords_vertex(glm::vec2& _vertex) const;

    };

    Picture* load_picture(const std::string& _path);

} /*LR*/

#endif // __PICTURE
