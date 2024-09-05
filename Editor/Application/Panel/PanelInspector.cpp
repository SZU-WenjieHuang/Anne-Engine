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

        auto reg = entity->GetRegistry();
        for(auto &&curr : reg->storage())
        {
            auto &storage = curr.second; // 某个特定类型的Component集合
            if (storage.contains(entity->GetEntity())) // 包含这个Entity的组件
            {
                entt::id_type id = curr.first; // ComponentID
                void *componentTypeAny = storage.get(entity->GetEntity()); // Component
                inspection::ComponentUIMap::Inspect(entity, id, componentTypeAny); //执行每一个Component的查找逻辑
            }     

            ImGui::Separator(); // 分割线

            // 可以选择的添加指定Component到Entity
            if (ImGui::BeginCombo("Add Component", "", ImGuiComboFlags_None))
            {
                auto &all_components_ctors = ComponentRegisterationMap::GetAllCtorFuncs();
                // 查找所有已注册的Component的Create函数
                for (auto &[name, ctor_func] : all_components_ctors)
                {
                    if (ImGui::Selectable(name.data()))
                    {
                        ctor_func(Selected::Instance().node->object);
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }
        }
    }
    ImGui::EndTabItem();
    ImGui::PopItemWidth();
}

void InspectorPanel::Show()
{
    if (m_show)
    {
        ListEntityAllComponents();
    }
}

/*
@brief 查询所有的SceneNode。并增加复选框来修改对应的Scene属性(是反射的一种了)
*/
void InspectorPanel::InspectSceneNode()
{
    auto &config = SceneManager::Instance().GetCurrentScene()->GetConfig();
    if (ImGui::CollapsingHeader("Scene Setting", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
    {
        // Todo:
        ImGui::Checkbox("Anti-Aliasing", &config.enable_antialias);
        if (ImGui::BeginItemTooltip())
        {
            ImGui::Text("Need to fix: AA does not work!");
            ImGui::EndTooltip();
        }
        // ImGui::Checkbox("Bloom", &config.enable_bloom);
        ImGui::Checkbox("Gamma Correction", &config.enable_gamma_correction);
        ImGui::Checkbox("HDR", &config.enable_hdr);
        ImGui::SliderFloat("Ambient Strength", &config.ambient_strength, 0.0f, 1.0f, "%.2f");
    }
}