#include <Draw_Modules/Draw_Module_Base.h>

using namespace LR;


INIT_FIELDS(LR::Draw_Module_Base_Stub, LV::Builder_Stub)
FIELDS_END



void Draw_Module_Base_Stub::M_init_constructed_product(LV::Variable_Base* _product) const
{
    Draw_Module_Base* product = (Draw_Module_Base*)_product;

    product->set_renderer(renderer);
}





INIT_FIELDS(LR::Draw_Module_Base, LV::Variable_Base)
FIELDS_END



void Draw_Module_Base::update(float /*_dt*/)
{
    L_ASSERT(m_renderer);

    glBindVertexArray(m_vertex_array);

    transformation_data()->update_matrix();

    m_renderer->setup_matrix(transformation_data()->matrix());
    m_renderer->setup_texture(texture());
    m_renderer->bind_vertex_array(vertex_array());

    m_renderer->draw(gl_draw_mode(), vertices().vertices_count());
}



Draw_Module_Base::Draw_Module_Base()
{

}

Draw_Module_Base::~Draw_Module_Base()
{

}
