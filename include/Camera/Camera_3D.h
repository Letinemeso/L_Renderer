#pragma once

#include <Math_Stuff.h>

#include <Window/Window_Controller.h>
#include <Camera/Camera_Base.h>


namespace LR
{

    class Camera_3D : public Camera_Base
    {
    public:
        struct Settings
        {
            glm::vec3 position, direction, top;
            float field_of_view = 0.0f, max_distance = 0.0f;
        };

    private:
        Settings m_settings;

    public:
        Camera_3D();
        Camera_3D(const Camera_3D& _other);

    public:
        void reconfigure();

        void set_settings(const Settings& _settings);

    public:
        inline Settings& settings() { return m_settings; }
        inline const Settings& settings() const { return m_settings; }

    };

}
