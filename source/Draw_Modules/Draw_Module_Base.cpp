#include <Draw_Modules/Draw_Module_Base.h>

using namespace LR;


INIT_FIELDS(LR::Draw_Module_Base_Stub, LV::Builder_Stub)
FIELDS_END



void Draw_Module_Base_Stub::M_init_constructed_product(LV::Variable_Base* _product) const
{
    Draw_Module_Base* product = (Draw_Module_Base*)_product;

    product->set_renderer(renderer);
    product->set_shader_transform_component(shader_transform_component);
}





INIT_FIELDS(LR::Draw_Module_Base, LV::Variable_Base)
FIELDS_END



void Draw_Module_Base::update(float /*_dt*/)
{
    L_ASSERT(m_renderer);
    L_ASSERT(m_shader_transform_component);

    glBindVertexArray(m_vertex_array);

    m_vertices.setup_buffer(m_shader_transform_component->vertex_attribs().coordinates.index, m_shader_transform_component->vertex_attribs().coordinates.floats_per_vertex);  //  theese magic numbers need to come from shader
    m_colors.setup_buffer(m_shader_transform_component->vertex_attribs().colors.index, m_shader_transform_component->vertex_attribs().colors.floats_per_vertex);
    m_texture.setup_buffer(m_shader_transform_component->vertex_attribs().texture_coordinates.index, m_shader_transform_component->vertex_attribs().texture_coordinates.floats_per_vertex);

    transformation_data()->update_matrix();

    m_shader_transform_component->set_projection_matrix(m_renderer->camera()->matrix());
    m_shader_transform_component->set_transform_matrix(transformation_data()->matrix());
    m_shader_transform_component->set_texture(texture());

    m_renderer->bind_vertex_array(vertex_array());

    m_renderer->draw(gl_draw_mode(), vertices().vertices_count());
}



Draw_Module_Base::Draw_Module_Base()
{
    glGenVertexArrays(1, &m_vertex_array);
    glBindVertexArray(m_vertex_array);

    m_vertices.set_vertex_array(&m_vertex_array);
    m_texture.set_vertex_array(&m_vertex_array);
    m_colors.set_vertex_array(&m_vertex_array);
}

Draw_Module_Base::~Draw_Module_Base()
{

}
