#pragma once
#include "Application/Basic/Common.h"
#include "Application/Basic/Selected.h"
#include "Application/Inspector/Inspector.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

namespace AnneEngine
{
    /*
    @brief 用于检查不同Entity的组件和属性
    */
    namespace Application
    {
        class InspectorPanel
        {
            public:
                using Ptr = std::unique_ptr<InspectorPanel>;
                InspectorPanel(const std::string &name, bool show);
                InspectorPanel() = delete;
                void Show();

                inline bool IsShow() 
                { 
                    return m_show; 
                }

                inline void SetShow(bool show) 
                { 
                    m_show = show; 
                }

            private:
                std::string m_name;
                bool m_show;
                void ListEntityAllComponents();  // 展示Entity的所有Component
                void InspectSceneNode();
        };
    }
}