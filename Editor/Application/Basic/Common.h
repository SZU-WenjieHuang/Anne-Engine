/*
在AnneEngine内，能打开访问管理各种本地文件资源的能力
*/

#pragma once
#include "Engine/AnneEngine.h"
#include "Application/FontAwesome/IconsFont.h"
#include "Application/FileBrowser/ImGuiFileDialog.h"
#include <utility>

namespace AnneEngine
{
    namespace common
    {
        inline static const std::string LoadModelLabel = "Load Model From File";
        inline static const std::string LoadModelToResourceLabel = "Load Model To Resourece From File";
        inline static const std::string LoadCubeMapLabel = "Load CubeMap From File";
        inline static const std::string SavingChooseDirectory = "Saving";
        inline static ImGuiStyle imgui_style;
        std::pair<std::string, std::string> ShowFileDiaglogue(std::string label);
        std::string ShowDirectoryDiaglogue(std::string label);
        void AlignForWidth(float width, float alignment = 0.5f);
    }
}