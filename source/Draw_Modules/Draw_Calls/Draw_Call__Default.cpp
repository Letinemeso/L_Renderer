#include <Draw_Modules/Draw_Calls/Draw_Call__Default.h>

#include <glew.h>
#include <Draw_Modules/Draw_Module.h>

using namespace LR;


void Draw_Call__Default::draw(const Draw_Module* _draw_module)
{
    glDrawArrays(_draw_module->draw_mode(), 0, _draw_module->calculate_vertices_amount());
}
