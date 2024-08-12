/*

Description: 
1. 组册UI检查工具。可以在运行时，对Entity的属性进行检查。
2. 类似反射机制

*/

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
// #include "Engine/Function/Component/All.h"
#include "Engine/Function/Entity.h"

namespace AnneEngine
{
    namespace inspection
    {
        // 函数类型 用于存储inspection函数
        using FromVoidType = std::function<void(AnneEngine::Entity::Ptr &, void *)>;

        // 具体的检查函数 会根据不同的模板入参来实现
        template <typename T>
        inline static void InspectComponent(AnneEngine::Entity::Ptr &entity, void *typeAny)
        {
        }     

        // 用unordered_map 来注册具体的Inspector函数

    }
}