#ifndef __TEXTURE
#define __TEXTURE

#include <glew.h>

#include <L_Debug/L_Debug.h>

#include <Components/Buffer.h>
#include <Picture/Picture.h>

namespace LR
{

    class Texture final : public LR::Buffer
    {
    private:
        unsigned int m_texture_object = 0;
        const Picture* m_picture = nullptr;

    public:
        Texture();
        Texture(const Picture* _picture, float* _tex_coords, unsigned int _tex_coords_count);
        Texture(const LR::Texture&) = delete;
        Texture(LR::Texture&&) = delete;
        void operator=(const LR::Texture&) = delete;
        void operator=(LR::Texture&&) = delete;

    public:
        void init(const Picture* _picture, const float* const _tex_coords, unsigned int _tex_coords_count);
        void set_picture(const Picture* _picture);
        void set_texture_coords(const float* const _tex_coords, unsigned int _tex_coords_count);
        void reconfigure_texture_coords();

        ~Texture();

    public:
        const Picture* get_picture() const;

    public:
        void bind() const;

    };

}

#endif
