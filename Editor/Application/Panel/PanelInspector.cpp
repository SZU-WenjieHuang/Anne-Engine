#include "Application/Panel/PanelInspector.h"
#include "Application/FontAwesome/IconsFont.h"

using namespace AnneEngine::Application;

InspectorPanel::InspectorPanel(const std::string &name, bool show) 
: m_name(name)
, m_show(show) 
{

}

/**
 * @brief Panel的展示入口
 */
void InspectorPanel::Show()
{
    if (m_show)
        ListEntityAllComponents();
}

/**
 * @brief 列出所有Components
 * @remark 为选定的实体显示所有其组件的属性，并允许用户通过下拉菜单添加新组件。
 */
void InspectorPanel::ListEntityAllComponents()
{
    std::string display_title = IconFont::WithIcon(ICON_FA_VECTOR_SQUARE, "Property");
    ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.64f);

    if (ImGui::BeginTabItem(display_title.c_str()) && Selected::Instance().node != nullptr)
    {
        // 选中ScenenNode
        if (SceneManager::Instance().GetCurrentSceneNode() == Selected::Instance().node)
        {
            InspectSceneNode();
        }

        // 反射该instance的所有组件 ECS系统 找Compinent先找entity
        auto &entity = Selected::Instance().node->object;
        if (entity == nullptr)
        {
            return;
        }
        
    }
}

/*
@brief 查询所有的SceneNode
*/
void InspectorPanel::InspectSceneNode()
{

}