#include <Draw_Rule/Draw_Rule.h>

#include <glew.h>
#include <Binds_Controller/Binds_Controller.h>

using namespace LR;


Draw_Rule::Draw_Rule()
{
    glGenVertexArrays(1, &m_vertex_array);
}

Draw_Rule::~Draw_Rule()
{
    glDeleteVertexArrays(1, &m_vertex_array);
}



void Draw_Rule::enable_attribute_array(unsigned int _index, unsigned int _floats_per_vertex)
{
    use();

    glEnableVertexAttribArray(_index);
}

void Draw_Rule::disable_attribute_array(unsigned int _index)
{
    use();

    glDisableVertexAttribArray(_index);
}



void Draw_Rule::use() const
{
    Binds_Controller::instance().bind_vertex_array(m_vertex_array);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Draw_Rule_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Draw_Rule_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    L_ASSERT(floats_per_vertex.size() == active_attribute_arrays.size());

    for(unsigned int i = 0; i < active_attribute_arrays.size(); ++i)
        product->enable_attribute_array(active_attribute_arrays[i], floats_per_vertex[i]);
}
