#include <Draw_Modules/Default_Draw_Module.h>

using namespace LR;


INIT_FIELDS(LR::Default_Draw_Module, LR::Draw_Module_Base)
FIELDS_END


Default_Draw_Module::Default_Draw_Module() : Draw_Module_Base()
{
    m_vertices.set_vertex_array(&m_vertex_array);
    m_texture.set_vertex_array(&m_vertex_array);
    m_colors.set_vertex_array(&m_vertex_array);
}

Default_Draw_Module::~Default_Draw_Module()
{

}



void Default_Draw_Module::init_vertices(const float *const _coords, unsigned int _coords_count)
{
    glBindVertexArray(m_vertex_array);
    m_vertices.init(_coords, _coords_count);
}

void Default_Draw_Module::init_colors(const float *const _colors, unsigned int _colors_count)
{
    glBindVertexArray(m_vertex_array);
    m_colors.init(_colors, _colors_count);
}

void Default_Draw_Module::init_texture(const Picture* _picture, const float *const tex_coords, unsigned int _tex_coords_count)
{
	glBindVertexArray(m_vertex_array);
    m_texture.set_picture(_picture);
    m_texture.set_texture_coords(tex_coords, _tex_coords_count);
    m_texture.reconfigure_texture_coords();
}


void Default_Draw_Module::set_texture(const Picture* _picture)
{
	glBindVertexArray(m_vertex_array);
	m_texture.set_picture(_picture);
}

void Default_Draw_Module::set_texture_coords(const float* _tc, unsigned int _tc_count)
{
	glBindVertexArray(m_vertex_array);
    m_texture.set_texture_coords(_tc, _tc_count);
}


void Default_Draw_Module::move_raw(const glm::vec3 &_stride)
{
    for(unsigned int i=0; i<m_vertices.size(); i += 3)
    {
        m_vertices[i] += _stride.x;
        m_vertices[i + 1] += _stride.y;
        m_vertices[i + 2] += _stride.z;
    }
}



void Default_Draw_Module::M_draw()
{
    m_renderer->draw(GL_TRIANGLES, vertices().vertices_count());
}



void Default_Draw_Module::update(float _dt)
{
    L_ASSERT(m_renderer);
    L_ASSERT(m_shader_transform_component);

    m_renderer->prepare();

    m_vertices.setup_buffer(m_shader_transform_component->vertex_attribs().coordinates.index, m_shader_transform_component->vertex_attribs().coordinates.floats_per_vertex);  //  theese magic numbers need to come from shader
    m_colors.setup_buffer(m_shader_transform_component->vertex_attribs().colors.index, m_shader_transform_component->vertex_attribs().colors.floats_per_vertex);
    m_texture.setup_buffer(m_shader_transform_component->vertex_attribs().texture_coordinates.index, m_shader_transform_component->vertex_attribs().texture_coordinates.floats_per_vertex);

    transformation_data()->update_matrix();

    m_shader_transform_component->set_projection_matrix(m_renderer->camera()->matrix());
    m_shader_transform_component->set_transform_matrix(transformation_data()->matrix());
    m_shader_transform_component->set_texture(texture());

    Draw_Module_Base::update(_dt);
}





INIT_FIELDS(LR::Default_Draw_Module_Stub, LR::Draw_Module_Base_Stub)

ADD_FIELD(std::string, texture_name)

ADD_FIELD(unsigned int, tcoords_count)
ADD_FIELD(float*, tcoords)

ADD_FIELD(unsigned int, coords_count)
ADD_FIELD(float*, coords)

ADD_FIELD(unsigned int, colors_count)
ADD_FIELD(float*, colors)

FIELDS_END


Default_Draw_Module_Stub::~Default_Draw_Module_Stub()
{
    delete[] coords;
    delete[] tcoords;
    delete[] colors;
}



LV::Variable_Base* Default_Draw_Module_Stub::M_construct_product() const
{
    return new Default_Draw_Module;
}

void Default_Draw_Module_Stub::M_init_constructed_product(LV::Variable_Base* _product) const
{
    Draw_Module_Base_Stub::M_init_constructed_product(_product);

    Default_Draw_Module* product = (Default_Draw_Module*)_product;

    product->set_shader_transform_component(shader_transform_component);

    product->init_vertices(coords, coords_count);
    product->init_colors(colors, colors_count);
    product->init_texture(graphic_resources_manager->get_picture(texture_name), tcoords, tcoords_count);
}
