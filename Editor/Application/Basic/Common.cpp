#include "Application/Basic/Common.h"

namespace AnneEngine
{
    namespace common
    {
        // 展示文件浏览器 并监听用户选择
        std::pair<std::string, std::string> ShowFileDiaglogue(std::string label)
        {
            ImVec2 maxSize = ImGui::GetMainViewport()->Size;
            ImVec2 minSize = maxSize * 0.45f;
            // display
            if (ImGuiFileDialog::Instance()->Display(label, ImGuiWindowFlags_NoCollapse, minSize, maxSize))
            {
                std::string filePathName, name;
                // action if OK
                if (ImGuiFileDialog::Instance()->IsOk())
                {
                    filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                    name = ImGuiFileDialog::Instance()->GetCurrentFileName();
                    name = name.substr(0, name.find_last_of("."));
                }
                // close
                ImGuiFileDialog::Instance()->Close();
                return {filePathName, name};
            }
            return {"", ""};
        }        

        // 展示用户的目录输入 并监听用户选择
        std::string ShowDirectoryDiaglogue(std::string label)
        {
            ImVec2 maxSize = ImGui::GetMainViewport()->Size;
            ImVec2 minSize = maxSize * 0.45f;
            // display
            if (ImGuiFileDialog::Instance()->Display(label, ImGuiWindowFlags_NoCollapse, minSize, maxSize))
            {
                std::string dirname;
                // action if OK
                if (ImGuiFileDialog::Instance()->IsOk())
                {
                    dirname = ImGuiFileDialog::Instance()->GetCurrentPath();
                }
                // close
                ImGuiFileDialog::Instance()->Close();
                return {dirname};
            }
            return "";
        }

        // UI的布局效果
        void AlignForWidth(float width, float alignment)
        {
            ImGuiStyle &style = ImGui::GetStyle();
            float avail = ImGui::GetContentRegionAvail().x;
            float off = (avail - width) * alignment;
            if (off > 0.0f)
            {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
            }
        }
    }
}