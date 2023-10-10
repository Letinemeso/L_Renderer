#ifndef RENDERER_H
#define RENDERER_H

#include <Camera/Camera_Base.h>
#include <Shader/Shader_Program.h>


namespace LR
{

    class Renderer
    {
    private:
        const Camera_Base* m_camera = nullptr;
        const Shader_Program* m_shader_program = nullptr;

    public:
        Renderer();
        Renderer(const Renderer& _other);
        void operator=(const Renderer& _other);
        Renderer(Renderer&& _other) = delete;
        void operator=(Renderer&& _other) = delete;

        ~Renderer();

    public:
        inline void set_camera(const Camera_Base* _camera) { m_camera = _camera; }
        inline void set_shader_program(const Shader_Program* _shader_program) { m_shader_program = _shader_program; }

    public:
        inline const Camera_Base* camera() const { return m_camera; }
        inline const Shader_Program* shader_program() const { return m_shader_program; }

    public:
        void setup_matrix(const glm::mat4x4& _transform_matrix);
        void setup_texture(const LR::Texture& _texture);
        void bind_vertex_array(unsigned int _vertex_array);

    public:
        void draw(unsigned int _draw_mode, unsigned int _vertices_amount) const;

    };

}


#endif // RENDERER_H
