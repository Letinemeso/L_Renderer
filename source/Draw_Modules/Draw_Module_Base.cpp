#include <Draw_Modules/Draw_Module_Base.h>

using namespace LR;



INIT_FIELDS(LR::Draw_Module_Base, LV::Variable_Base)
FIELDS_END



void Draw_Module_Base::update(float /*_dt*/)
{
    glBindVertexArray(m_vertex_array);

    transformation_data()->update_matrix();

    m_renderer->bind_vertex_array(vertex_array());

    M_draw();
}



Draw_Module_Base::Draw_Module_Base()
{
    glGenVertexArrays(1, &m_vertex_array);
    glBindVertexArray(m_vertex_array);
}

Draw_Module_Base::~Draw_Module_Base()
{
    glDeleteVertexArrays(1, &m_vertex_array);
}





INIT_FIELDS(LR::Draw_Module_Base_Stub, LEti::Module_Stub)
FIELDS_END



void Draw_Module_Base_Stub::M_init_constructed_product(LV::Variable_Base* _product) const
{
    Draw_Module_Base* product = (Draw_Module_Base*)_product;

    product->set_renderer(renderer);
}
