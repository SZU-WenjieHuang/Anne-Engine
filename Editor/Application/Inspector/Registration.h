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

        // 具体的检查函数 会根据不同的模板入参来重载
        template <typename T>
        inline static void InspectComponent(AnneEngine::Entity::Ptr &entity, void *typeAny)
        {
        }     

        class ComponentUIMap
        {
        private:
            // 映射表 从id到具体的ui函数
            inline static std::unordered_map<entt::id_type, inspection::FromVoidType> idtype_to_uiFunc;

        public:

            /*
            @brief type转成hash 作为key， Inspector函数 是Value
            */ 
            template<typename T>
            inline static void Register()
            {
                idtype_to_uiFunc[entt::type_id<T>().hash()] = &inspection::InspectComponent<T>;
            }


            /*
            @brief 查找函数，若有对应id的函数，则inspect
            @param entity  查询函数的入参
            @param typeAny 查询函数的入参
            @param id 查询函数的id
            */ 
            inline static void Inspect(AnneEngine::Entity::Ptr &entity, entt::id_type id, void *&typeAny)
            {
                if (idtype_to_uiFunc.find(id) == idtype_to_uiFunc.end())
                {
                    return;
                }
                else
                {
                    idtype_to_uiFunc[id](entity, typeAny);
                }
            }
        };

    }
}