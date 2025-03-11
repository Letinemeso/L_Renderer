#pragma once

#include <Data_Structures/Vector.h>


namespace LR
{

    class Binds_Controller
    {
    public:
        struct OpenGL_State
        {
            unsigned int vertex_array = 0;
            unsigned int frame_buffer = 0;
            LDS::Vector<unsigned int> bound_textures;
        };

    private:
        OpenGL_State m_current_state;

    private:
        Binds_Controller();

        Binds_Controller(const Binds_Controller& _other) = delete;
        Binds_Controller(Binds_Controller&& _other) = delete;
        void operator=(const Binds_Controller& _other) = delete;
        void operator=(Binds_Controller&& _other) = delete;

    public:
        inline static Binds_Controller& instance() { static Binds_Controller controller; return controller; }

    public:
        inline OpenGL_State save_state() const { return m_current_state; }
        inline unsigned int save_vertex_array() const { return m_current_state.vertex_array; }
        inline unsigned int save_frame_buffer() const { return m_current_state.frame_buffer; }
        inline unsigned int save_bound_texture(unsigned int _texture_id) const { return m_current_state.bound_textures[_texture_id]; }
        inline LDS::Vector<unsigned int> save_bound_textures() const { return m_current_state.bound_textures; }

    public:
        void restore_state(const OpenGL_State& _state);
        void bind_vertex_array(unsigned int _vertex_array_id);
        void bind_frame_buffer(unsigned int _frame_buffer_id);
        void bind_texture(unsigned int _texture_id, unsigned int _texture_object_id);
        void bind_textures(const LDS::Vector<unsigned int>& _bound_textures_ids);

    };

}
