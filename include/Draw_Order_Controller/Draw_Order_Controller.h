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
        using Sort_Function = LST::Function<bool(const LEti::Object*, const LEti::Object*)>;

    private:
        using Registered_Modules = LDS::Map<LEti::Module*, Draw_Function>;
        using Registred_Modules_Locations = LDS::Map<LEti::Module*, Registered_Modules*>;

        struct Draw_Layer_Data
        {
            std::string name;
            Registered_Modules modules_set;
            Before_Draw_Function before_draw;
            Sort_Function sort_function;
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
            inline Draw_Layer_Settings& set_before_draw_function(const Before_Draw_Function& _func) { m_data.before_draw = _func; return *this; }
            inline Draw_Layer_Settings& set_sort_function(const Sort_Function& _func) { m_data.sort_function = _func; return *this; }

        };

    private:
        Draw_Layers m_draw_layers;
        Registred_Modules_Locations m_registred_modules_locations;

    private:
        Registered_Modules& M_get_modules_set_for_layer(const std::string& _layer_name);

    public:
        Draw_Layer_Settings add_layer(const std::string& _name);

    public:
        void register_module(const std::string& _layer_name, LEti::Module* _module, const Draw_Function& _draw_function);
        void unregister_module(LEti::Module* _module);

        bool is_module_registred(LEti::Module* _module);

    private:
        void M_draw_default(const Registered_Modules& _modules) const;
        void M_draw_sorted(const Registered_Modules& _modules, const Sort_Function& _func) const;

    public:
        void draw() const;

    };

}
