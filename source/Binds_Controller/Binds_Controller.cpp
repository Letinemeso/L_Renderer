#include <Binds_Controller/Binds_Controller.h>

#include <glew.h>

using namespace LR;


Binds_Controller::Binds_Controller()
{
    int max_textures_amount = 0;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_textures_amount);
    m_current_state.bound_textures.resize_and_fill(max_textures_amount, 0);
}



void Binds_Controller::restore_state(const OpenGL_State &_state)
{
    bind_vertex_array(_state.vertex_array);
    bind_frame_buffer(_state.frame_buffer);
    bind_textures(_state.bound_textures);
}

void Binds_Controller::bind_vertex_array(unsigned int _vertex_array_id)
{
    m_current_state.vertex_array = _vertex_array_id;
    glBindVertexArray(_vertex_array_id);
}

void Binds_Controller::bind_frame_buffer(unsigned int _frame_buffer_id)
{
    m_current_state.frame_buffer = _frame_buffer_id;
    glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer_id);
}

void Binds_Controller::bind_texture(unsigned int _texture_id, unsigned int _texture_object_id)
{
    m_current_state.bound_textures[_texture_id] = _texture_object_id;

    glActiveTexture(GL_TEXTURE0 + _texture_id);
    glBindTexture(GL_TEXTURE_2D, _texture_object_id);
}

void Binds_Controller::bind_textures(const LDS::Vector<unsigned int>& _bound_textures_ids)
{
    for(unsigned int i=0; i<_bound_textures_ids.size(); ++i)
        bind_texture(i, _bound_textures_ids[i]);
}
