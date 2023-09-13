#include <Draw_Modules/Default_Draw_Module_2D.h>

using namespace LR;


INIT_FIELDS(LR::Default_Draw_Module_2D_Stub, LR::Draw_Module_Base_Stub)

ADD_FIELD(std::string, texture_name)

ADD_FIELD(unsigned int, tcoords_count)
ADD_FIELD(float*, tcoords)

ADD_FIELD(unsigned int, coords_count)
ADD_FIELD(float*, coords)

ADD_FIELD(unsigned int, colors_count)
ADD_FIELD(float*, colors)

FIELDS_END


INIT_FIELDS(LR::Default_Draw_Module_2D, LR::Draw_Module_Base)
FIELDS_END



Default_Draw_Module_2D_Stub::~Default_Draw_Module_2D_Stub()
{
    delete[] coords;
    delete[] tcoords;
    delete[] colors;
}



LV::Variable_Base* Default_Draw_Module_2D_Stub::M_construct_product() const
{
    return new Default_Draw_Module_2D;
}

void Default_Draw_Module_2D_Stub::M_init_constructed_product(LV::Variable_Base* _product) const
{
    Draw_Module_Base_Stub::M_init_constructed_product(_product);

    Default_Draw_Module_2D* result = (Default_Draw_Module_2D*)_product;

    result->init_vertices(coords, coords_count);
    result->init_colors(colors, colors_count);
    result->init_texture(graphics_resources_manager->get_picture(texture_name), tcoords, tcoords_count);
}



Default_Draw_Module_2D::Default_Draw_Module_2D() : Draw_Module_Base()
{

}

Default_Draw_Module_2D::~Default_Draw_Module_2D()
{
	glDeleteVertexArrays(1, &m_vertex_array);
}



void Default_Draw_Module_2D::init_vertices(const float *const _coords, unsigned int _coords_count)
{
    glBindVertexArray(m_vertex_array);
    m_vertices.init(_coords, _coords_count);
}

void Default_Draw_Module_2D::init_colors(const float *const _colors, unsigned int _colors_count)
{
    glBindVertexArray(m_vertex_array);
    m_colors.init(_colors, _colors_count);
}

void Default_Draw_Module_2D::init_texture(const Picture* _picture, const float *const tex_coords, unsigned int _tex_coords_count)
{
	glBindVertexArray(m_vertex_array);
    m_texture.set_picture(_picture);
    m_texture.set_texture_coords(tex_coords, _tex_coords_count);
    m_texture.reconfigure_texture_coords();
}


void Default_Draw_Module_2D::set_texture(const Picture* _picture)
{
	glBindVertexArray(m_vertex_array);
	m_texture.set_picture(_picture);
}

void Default_Draw_Module_2D::set_texture_coords(const float* _tc, unsigned int _tc_count)
{
	glBindVertexArray(m_vertex_array);
    m_texture.set_texture_coords(_tc, _tc_count);
}


void Default_Draw_Module_2D::move_raw(const glm::vec3 &_stride)
{
    for(unsigned int i=0; i<m_vertices.size(); i += 3)
    {
        m_vertices[i] += _stride.x;
        m_vertices[i + 1] += _stride.y;
        m_vertices[i + 2] += _stride.z;
    }
}



void Default_Draw_Module_2D::update(float _dt)
{
    Draw_Module_Base::update(_dt);
}
