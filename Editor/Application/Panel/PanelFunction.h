#pragma once

#include "Application/Basic/Selected.h"
#include "Application/Basic/Common.h"
#include "Application/Inspector/Inspector.h"
#include "Application/Inspector/ModelPreview.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

namespace AnneEngine
{
    namespace Application
    {
        /*
        @brief 功能面板
        */
        class FunctionPanel
        {

        public:
            FunctionPanel(const std::string &name, bool show);
            FunctionPanel() = delete;

            using Ptr = std::unique_ptr<FunctionPanel>;

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
            std::unordered_map<std::string, Texture2D::Ptr> m_resource_icons;
            std::string m_name;
            bool m_show;
            bool m_show_debug;
            void ResourcePanel();
            void ConsolePanel();
            void FileDiaglogues();
        };
    }
}