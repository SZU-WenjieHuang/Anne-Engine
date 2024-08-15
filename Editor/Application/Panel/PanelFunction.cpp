#include "Application/Panel/PanelFunction.h"
#include "Application/FontAwesome/IconsFont.h"
#include "Engine/AnneEngine.h"

using namespace AnneEngine::Application;

// 构造函数 初始化两个Icon
FunctionPanel::FunctionPanel(const std::string &name, bool show) 
: m_name(name)
, m_show(show)
{
    inspection::ModelPreview::Init();
    m_resource_icons["ModelFileImage"] = std::make_shared<Texture2D>("Images/model_icon.png");
    m_resource_icons["ModelAddImage"] = std::make_shared<Texture2D>("Images/model_add_icon.png");
}

// 展示FunctPanel，包括 ResourcePanel + ConsolePanel
void FunctionPanel::Show()
{
    if (m_show)
    {
        auto window_size = ImGui::GetWindowSize();
        ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y), ImGuiCond_Once);
        ImGui::Begin("Function", &m_show, ImGuiWindowFlags_NoCollapse);

        // 创建标签栏TabBar
        if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
        {
            ResourcePanel();
            ConsolePanel();
            ImGui::EndTabBar();
        }

        // 文本对话框
        FileDiaglogues();
        ImGui::End();
    }
}

void FunctionPanel::ConsolePanel()
{
    // ICON_FA_TABLE 是FontAwsome中的一个图标
    std::string display_title = IconFont::WithIcon(ICON_FA_TABLE, "Console");

    // 开始Panel绘制
    if (ImGui::BeginTabItem(display_title.c_str()))
    {
        // 内部创建Button
        ImGui::Button("TODO", ImGui::GetContentRegionAvail());
        if (ImGui::BeginItemTooltip())
        {
            // 鼠标悬停时候的提示文字
            ImGui::Text("This function will be added in furture version.");
            ImGui::EndTooltip();
        }

        ImGui::EndTabItem();
    }
}

void FunctionPanel::ResourcePanel()
{
    std::string display_title = IconFont::WithIcon(ICON_FA_CUBES_STACKED, "Resource");

    auto buildin_mesh_name = AnneEngine::MeshManager::Instance().GetBuildInMeshsName();
    auto isbuildin = [&](std::string val)
    {
        for (auto x : buildin_mesh_name)
            if (val == x)
                return true;
        return false;
    };

    // show tab
    if (ImGui::BeginTabItem(display_title.c_str()))
    {
        auto mesh_table_column = 3;
        auto all_names = MeshManager::Instance().GetAllMeshListName();
        auto model_icon = m_resource_icons["ModelFileImage"]->GetID();
        auto region_avail = ImGui::GetContentRegionAvail();
        std::string wait_delete_mesh_name;
        if (ImGui::BeginTable("MeshResource", mesh_table_column, ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable))
        {
            auto row_height = ImGui::GetCurrentTable()->RowMinHeight;
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Path");
            ImGui::TableSetupColumn("Meshs");
            ImGui::TableHeadersRow();
            auto size = ImGui::GetContentRegionAvail();
            for (auto &mesh_name : all_names)
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                auto buildin = isbuildin(mesh_name);
                auto last_slash = buildin ? 0 : mesh_name.find_last_of("/\\") + 1;
                auto obj_name = mesh_name.substr(last_slash, mesh_name.size() - last_slash);
                ImGui::Text(IconFont::WithIcon(ICON_FA_SHAPES, obj_name).c_str());
                if (ImGui::BeginPopupContextItem(mesh_name.c_str()))
                {
                    if (!buildin && ImGui::MenuItem("Delete"))
                    {
                        wait_delete_mesh_name = mesh_name;
                    }

                    ImGui::EndPopup();
                }
                ImGui::TableSetColumnIndex(1);
                auto mesh_path = buildin ? "Build-In" : mesh_name.c_str();
                ImGui::Text(mesh_path);
                ImGui::TableSetColumnIndex(2);
                ImGui::Text("%d", MeshManager::Instance().GetMeshsCount(mesh_name));
            }
            ImGui::EndTable();

            // 添加导入模型按钮
            if (ImGui::Button(ICON_FA_PLUS, ImVec2(region_avail.x, row_height)))
            {
                IGFD::FileDialogConfig config;
                config.path = ".";
                config.sidePaneWidth = 400;
                const char *filters = "Model files (*.obj *.glb *.gltf){.obj,.glb,.gltf}";
                ImGuiFileDialog::Instance()->OpenDialog(common::LoadModelToResourceLabel, "Choose File", filters, config);
            }
        }
        ImGui::EndTabItem();

        // 删除待删除的内容
        if (!wait_delete_mesh_name.empty())
        {
            MeshManager::Instance().DeleteMeshList(wait_delete_mesh_name);
        }
    }
}

void FunctionPanel::FileDiaglogues()
{
    // 用户选中了文件 就给导入
    auto getfile = common::ShowFileDiaglogue(common::LoadModelToResourceLabel);
    if (getfile.first != "" && getfile.second != "")
    {
        MeshManager::Instance().Import(getfile.first);
    }
}