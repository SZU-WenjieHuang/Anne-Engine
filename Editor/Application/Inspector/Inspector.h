#pragma once
#include "Application/Inspector/Registration.h"
#include "Application/FileBrowser/ImGuiFileDialog.h"
#include "Application/FontAwesome/IconsFont.h"
#include "Engine/AnneEngine.h"
#include "Third/imgui/imgui_stdlib.h"

namespace AnneEngine
{
    namespace inspection
    {
        // non-component material
        // void InspectNonComponent(PBRMaterial::Ptr &pbrmat); // 尚未定义

        inline static void Init()
        {
            // ComponentUIMap::Register<component::NameComponent>();
            // ComponentUIMap::Register<component::ActiveComponent>();
            // ComponentUIMap::Register<component::Transform>();
            // ComponentUIMap::Register<component::MeshData>();
            // ComponentUIMap::Register<component::PointLight>();
            // ComponentUIMap::Register<component::DirectionalLight>();
            // ComponentUIMap::Register<component::AreaLight>();
            // ComponentUIMap::Register<component::Camera>();
            // ComponentUIMap::Register<component::IBLCubeMap>();
            // ComponentUIMap::Register<component::ScreenSpaceReflection>();
            // ComponentUIMap::Register<component::VoxelGlobalIllumination>();
        }
        
        // 各种 component的 Inspect函数的具体重载实现
    }
}