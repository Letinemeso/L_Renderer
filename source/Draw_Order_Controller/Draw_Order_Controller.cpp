#include <Draw_Order_Controller/Draw_Order_Controller.h>

using namespace LR;


Draw_Order_Controller::Registred_Modules& Draw_Order_Controller::M_get_modules_set_for_layer(const std::string& _layer_name)
{
    for(Draw_Layers::Iterator it = m_draw_layers.begin(); !it.end_reached(); ++it)
    {
        if(it->name == _layer_name)
            return it->modules_set;
    }

    L_ASSERT(false);
}



void Draw_Order_Controller::add_layer(const std::string& _name)
{
    L_DEBUG_FUNC_1ARG(
        [this](const std::string& _name)
        {
            for(Draw_Layers::Iterator it = m_draw_layers.begin(); !it.end_reached(); ++it)
            {
                L_ASSERT(it->name != _name);
            }
        }, _name);

    m_draw_layers.push_back({ _name, {} });
}



void Draw_Order_Controller::register_module(const std::string& _layer_name, LEti::Module* _module, const Draw_Function& _draw_function)
{
    L_ASSERT(_module);
    L_ASSERT(_draw_function);
    L_ASSERT(!m_registred_modules_locations.find(_module).is_ok());

    Registred_Modules& modules_in_layer = M_get_modules_set_for_layer(_layer_name);
    modules_in_layer.insert(_module, _draw_function);

    m_registred_modules_locations.insert(_module, &modules_in_layer);
}

void Draw_Order_Controller::unregister_module(LEti::Module* _module)
{
    Registred_Modules_Locations::Iterator module_location_it = m_registred_modules_locations.find(_module);
    L_ASSERT(module_location_it.is_ok());

    Registred_Modules& module_location = **module_location_it;

    Registred_Modules::Iterator module_it = module_location.find(_module);
    L_ASSERT(module_it.is_ok());

    module_location.erase(module_it);
    m_registred_modules_locations.erase(module_location_it);
}



void Draw_Order_Controller::draw() const
{
    for(Draw_Layers::Const_Iterator layer_it = m_draw_layers.begin(); !layer_it.end_reached(); ++layer_it)
    {
        const Registred_Modules& modules_set = layer_it->modules_set;
        for(Registred_Modules::Const_Iterator module_it = modules_set.iterator(); !module_it.end_reached(); ++module_it)
        {
            const Draw_Function& draw_function = *module_it;
            draw_function();
        }
    }
}
