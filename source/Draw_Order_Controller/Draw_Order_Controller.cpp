#include <Draw_Order_Controller/Draw_Order_Controller.h>

#include <Stuff/Sorter.h>

using namespace LR;


Draw_Order_Controller::Draw_Layer_Data& Draw_Order_Controller::M_find_layer(const std::string& _layer_name)
{
    for(Draw_Layers::Iterator it = m_draw_layers.begin(); !it.end_reached(); ++it)
    {
        Draw_Layer_Data& layer = *it;

        if(layer.name == _layer_name)
            return layer;
    }

    L_ASSERT(false);
    return *m_draw_layers.begin();      //  this should never happen
}

const Draw_Order_Controller::Draw_Layer_Data& Draw_Order_Controller::M_find_layer(const std::string& _layer_name) const
{
    for(Draw_Layers::Const_Iterator it = m_draw_layers.begin(); !it.end_reached(); ++it)
    {
        const Draw_Layer_Data& layer = *it;

        if(layer.name == _layer_name)
            return layer;
    }

    L_ASSERT(false);
    return *m_draw_layers.begin();      //  this should never happen
}



Draw_Order_Controller::Draw_Layer_Settings Draw_Order_Controller::add_layer(const std::string& _name)
{
    L_DEBUG_FUNC_1ARG(
        [this](const std::string& _name)
        {
            for(Draw_Layers::Iterator it = m_draw_layers.begin(); !it.end_reached(); ++it)
            {
                Draw_Layer_Data& layer = *it;
                L_ASSERT(layer.name != _name);
            }
        }, _name);

    m_draw_layers.push_back({ _name, {} });

    Draw_Layer_Data& layer = *m_draw_layers.end();
    return Draw_Layer_Settings(layer);
}

Draw_Order_Controller::Draw_Layer_Settings Draw_Order_Controller::configure_layer(const std::string& _name)
{
    Draw_Layer_Data& layer = M_find_layer(_name);
    return Draw_Layer_Settings(layer);
}



void Draw_Order_Controller::register_module(const std::string& _layer_name, LEti::Module* _module, const Draw_Function& _draw_function)
{
    L_ASSERT(_module);
    L_ASSERT(_draw_function);
    L_ASSERT(!m_registred_modules_locations.find(_module).is_ok());

    Registered_Modules& modules_in_layer = M_find_layer(_layer_name).modules_set;
    modules_in_layer.insert(_module, _draw_function);

    m_registred_modules_locations.insert(_module, &modules_in_layer);
}

void Draw_Order_Controller::unregister_module(LEti::Module* _module)
{
    Registred_Modules_Locations::Iterator module_location_it = m_registred_modules_locations.find(_module);
    L_ASSERT(module_location_it.is_ok());

    Registered_Modules& module_location = **module_location_it;

    Registered_Modules::Iterator module_it = module_location.find(_module);
    L_ASSERT(module_it.is_ok());

    module_location.erase(module_it);
    m_registred_modules_locations.erase(module_location_it);
}


bool Draw_Order_Controller::is_module_registred(LEti::Module* _module)
{
    Registred_Modules_Locations::Iterator module_location_it = m_registred_modules_locations.find(_module);
    return module_location_it.is_ok();
}



void Draw_Order_Controller::M_draw_default(const Registered_Modules& _modules) const
{
    for(Registered_Modules::Const_Iterator module_it = _modules.iterator(); !module_it.end_reached(); ++module_it)
    {
        const Draw_Function& draw_function = *module_it;
        draw_function();
    }
}

void Draw_Order_Controller::M_draw_sorted(const Registered_Modules& _modules, const Sort_Function& _func) const
{
    L_ASSERT(_func);

    LDS::Vector<Registered_Modules::Const_Iterator> vec_to_sort(_modules.size());

    for(Registered_Modules::Const_Iterator module_it = _modules.iterator(); !module_it.end_reached(); ++module_it)
        vec_to_sort.push(module_it);

    LST::Sorter<Registered_Modules::Const_Iterator> sorter([&_func](const Registered_Modules::Const_Iterator& _first, const Registered_Modules::Const_Iterator& _second)
    {
        return _func(_first.key()->parent_object(), _second.key()->parent_object());
    });
    sorter.sort(vec_to_sort);

    for(unsigned int i = 0; i < vec_to_sort.size(); ++i)
    {
        const Draw_Function& draw = *(vec_to_sort[i]);
        draw();
    }
}



void Draw_Order_Controller::draw() const
{
    for(Draw_Layers::Const_Iterator it = m_draw_layers.begin(); !it.end_reached(); ++it)
    {
        const Draw_Layer_Data& layer = *it;

        const Camera_Base* previous_camera = m_renderer->camera();
        m_renderer->set_camera(layer.camera);

        if(layer.before_draw)
            layer.before_draw();

        const Registered_Modules& modules_set = layer.modules_set;

        if(layer.sort_function)
            M_draw_sorted(modules_set, layer.sort_function);
        else
            M_draw_default(modules_set);

        m_renderer->set_camera(previous_camera);
    }
}

void Draw_Order_Controller::draw_layer(const std::string& _layer_name) const
{
    const Draw_Layer_Data& layer = M_find_layer(_layer_name);

    const Camera_Base* previous_camera = m_renderer->camera();
    m_renderer->set_camera(layer.camera);

    if(layer.before_draw)
        layer.before_draw();

    const Registered_Modules& modules_set = layer.modules_set;

    if(layer.sort_function)
        M_draw_sorted(modules_set, layer.sort_function);
    else
        M_draw_default(modules_set);

    m_renderer->set_camera(previous_camera);
}
