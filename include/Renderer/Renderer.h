#pragma once

#include <Camera/Camera_Base.h>
#include <Shader/Shader_Program.h>

#include <Draw_Modules/Draw_Module.h>


namespace LR
{

    class Renderer
    {
    private:
        const Camera_Base* m_camera = nullptr;

    public:
        Renderer();
        Renderer(const Renderer& _other);
        void operator=(const Renderer& _other);
        Renderer(Renderer&& _other) = delete;
        void operator=(Renderer&& _other) = delete;

        ~Renderer();

    public:
        inline void set_camera(const Camera_Base* _camera) { m_camera = _camera; }

    public:
        inline const Camera_Base* camera() const { return m_camera; }

    };

}
