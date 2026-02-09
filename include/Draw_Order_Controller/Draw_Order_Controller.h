#pragma once

#include <Stuff/Function_Wrapper.h>
#include <Data_Structures/Map.h>
#include <Data_Structures/List.h>

#include <Module.h>

#include <Camera/Camera_Base.h>
#include <Renderer/Renderer.h>


namespace LR
{

    class Draw_Order_Controller
    {
    public:
        using Draw_Function = LST::Function<void()>;
        using Before_Draw_Function = LST::Function<void()>;
        using Sort_Function = LST::Function<bool(const LEti::Object*, const LEti::Object*)>;
        using Visibility_Check_Function = LST::Function<bool(const LEti::Module*)>;

    private:
        using Registered_Modules = LDS::Map<LEti::Module*, Draw_Function>;
        using Registred_Modules_Locations = LDS::Map<LEti::Module*, Registered_Modules*>;

        struct Draw_Layer_Data
        {
            std::string name;
            Registered_Modules modules_set;
            Before_Draw_Function before_draw;
            Sort_Function sort_function;
            Visibility_Check_Function visiblity_check_function;
            const LR::Camera_Base* camera = nullptr;
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
            inline Draw_Layer_Settings& set_visibility_check_function(const Visibility_Check_Function& _func) { m_data.visiblity_check_function = _func; return *this; }
            inline Draw_Layer_Settings& set_camera(const LR::Camera_Base* _camera) { m_data.camera = _camera; return *this; }

        };

    private:
        Draw_Layers m_draw_layers;
        Registred_Modules_Locations m_registred_modules_locations;

        LR::Renderer* m_renderer = nullptr;

    public:
        inline void inject_renderer(LR::Renderer* _ptr) { m_renderer = _ptr; }

    private:
        Draw_Layer_Data& M_find_layer(const std::string& _layer_name);
        const Draw_Layer_Data& M_find_layer(const std::string& _layer_name) const;

    public:
        Draw_Layer_Settings add_layer(const std::string& _name);
        Draw_Layer_Settings configure_layer(const std::string& _name);

    public:
        void register_module(const std::string& _layer_name, LEti::Module* _module, const Draw_Function& _draw_function);
        void unregister_module(LEti::Module* _module);

        bool is_module_registred(LEti::Module* _module);

    private:
        void M_draw_default(const Registered_Modules& _modules, const Visibility_Check_Function& _visibility_check_function) const;
        void M_draw_sorted(const Registered_Modules& _modules, const Sort_Function& _func, const Visibility_Check_Function& _visibility_check_function) const;

        void M_draw_layer(const Draw_Layer_Data& _layer) const;

    public:
        void draw() const;
        void draw_layer(const std::string& _layer_name) const;

    };

}
