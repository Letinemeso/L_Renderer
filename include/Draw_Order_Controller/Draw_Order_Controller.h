#pragma once

#include <Stuff/Function_Wrapper.h>
#include <Data_Structures/Map.h>
#include <Data_Structures/List.h>

#include <Module.h>


namespace LR
{

    class Draw_Order_Controller
    {
    public:
        using Draw_Function = LST::Function<void()>;
        using Before_Draw_Function = LST::Function<void()>;

    private:
        using Registred_Modules = LDS::Map<LEti::Module*, Draw_Function>;
        using Registred_Modules_Locations = LDS::Map<LEti::Module*, Registred_Modules*>;

        struct Draw_Layer_Data
        {
            std::string name;
            Registred_Modules modules_set;
            Before_Draw_Function before_draw;
        };

        using Draw_Layers = LDS::List<Draw_Layer_Data>;

    public:
        class Draw_Layer_Settings
        {
        private:
            Draw_Layer_Data& m_data;

        private:
            friend class Draw_Order_Controller;
            Draw_Layer_Settings(Draw_Layer_Data& _data) : m_data(_data) { }

        public:
            inline void set_before_draw_function(const Before_Draw_Function& _func) { m_data.before_draw = _func; }

        };

    private:
        Draw_Layers m_draw_layers;
        Registred_Modules_Locations m_registred_modules_locations;

    private:
        Registred_Modules& M_get_modules_set_for_layer(const std::string& _layer_name);

    public:
        Draw_Layer_Settings add_layer(const std::string& _name);

    public:
        void register_module(const std::string& _layer_name, LEti::Module* _module, const Draw_Function& _draw_function);
        void unregister_module(LEti::Module* _module);

        bool is_module_registred(LEti::Module* _module);

    public:
        void draw() const;

    };

}
