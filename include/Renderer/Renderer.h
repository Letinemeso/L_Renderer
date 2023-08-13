#ifndef RENDERER_H
#define RENDERER_H

#include <Camera/Camera_Base.h>
#include <Shader/Shader.h>


namespace LR
{

    class Renderer
    {
    private:
        const Camera_Base* m_camera = nullptr;
        const Shader* m_shader = nullptr;

    public:
        Renderer();
        Renderer(const Renderer& _other);
        void operator=(const Renderer& _other);
        Renderer(Renderer&& _other) = delete;
        void operator=(Renderer&& _other) = delete;

        ~Renderer();

    public:
        inline void set_camera(const Camera_Base* _camera) { m_camera = _camera; }
        inline void set_shader(const Shader* _shader) { m_shader = _shader; }

    public:
        inline const Camera_Base* camera() const { return m_camera; }
        inline const Shader* shader() const { return m_shader; }

    public:
        void setup_matrix(const glm::mat4x4& _transform_matrix);
        void setup_texture(const LR::Texture& _texture);
        void bind_vertex_array(unsigned int _vertex_array);

    public:
        void draw(unsigned int _draw_mode, unsigned int _vertices_amount) const;

    };

}


#endif // RENDERER_H
