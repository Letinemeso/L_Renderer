#pragma once

#include <Stuff/Timer.h>

#include <Draw_Modules/Draw_Module_Base.h>
#include <Components/Graphics_Component__Texture.h>


namespace LR
{

    class Draw_Module__Animation : public Draw_Module
    {
    public:
        DECLARE_VARIABLE;

    private:
        unsigned int m_frames_count = 0;
        unsigned int m_fps = 0;
        float m_time_before_next_frame = 0.0f;
        float m_frame_offset_ratio = 0.0f;

        unsigned int m_current_frame = 0;

    private:
        bool m_is_paused = true;
        LST::Timer m_frame_update_timer;
        unsigned int m_times_to_repeat = 0;
        unsigned int m_repetitions = 0;

    private:
        Graphics_Component__Texture* m_texture = nullptr;

    public:
        Draw_Module__Animation();

    public:
        inline void set_texture(Graphics_Component__Texture* _ptr) { m_texture = _ptr; }

    private:
        void M_update_frame(float _dt);

    public:
        void update(float _dt) override;

    public:
        void set_animation_data(unsigned int _frames_count);
        void set_fps(unsigned int _fps);
        void set_frame(unsigned int _frame);

        void start(unsigned int _cycles = 0);
        void pause();
        void unpause();

    public:
        inline unsigned int frames_count() const { return m_frames_count; }
        inline unsigned int fps() const { return m_fps; }
        inline unsigned int current_frame() const { return m_current_frame; }
        inline unsigned int repetitions() const { return m_repetitions; }
        inline bool paused() const { return m_is_paused; }

    };

    class Draw_Module__Animation__Stub : public Draw_Module_Stub
    {
    public:
        DECLARE_VARIABLE;

    public:
        unsigned int frames_per_second = 0;
        unsigned int frames_count = 0;
        unsigned int times_to_repeat = 0;

    public:
        Graphics_Component_Stub__Texture* texture_stub = new Graphics_Component_Stub__Texture;

    public:
        ~Draw_Module__Animation__Stub();

    protected:
        LV::Variable_Base* M_construct_product() const override;
        void M_init_constructed_product(LV::Variable_Base* _product) const override;

    };

}
