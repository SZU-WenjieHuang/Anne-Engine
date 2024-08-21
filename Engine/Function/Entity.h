// 暂时定义一个空的接口头文件

#pragma once
#include "Engine/Core/Singleton.hpp"
#include "Engine/Core/SubSystem.hpp"
#include "Third/entt/entt.hpp"
#include "Engine/Core/Serialization.h"
#include <iostream>

namespace AnneEngine
{
    /**
     * @brief Entity的序列化与反序列化函数 
    */
    class ComponentSerilizationMap
    {
        friend class ComponentRegisterationMap;

    private:
        inline static std::unordered_map<entt::id_type, std::string> idtype_to_name;                          // 从id到名字
        inline static std::unordered_map<entt::id_type, serialization::FromVoidTypeFunc> idtype_to_regFunc;   // 序列化函数
        inline static std::unordered_map<std::string, serialization::BindComponentFunc> str_to_bindFunc;      // 反序列化函数
    
    public:
        inline static std::string GetName(entt::id_type id) { return idtype_to_name[id]; }
        inline static nlohmann::json GetJsonFromVoidType(entt::id_type id, void *typeAny) { return idtype_to_regFunc[id](typeAny); }
        inline static serialization::BindComponentFunc &GetBindFunc(std::string &componentType) { return str_to_bindFunc[componentType]; }       
    };

    class Entity
    {
    public:
        using Ptr = std::shared_ptr<Entity>;

    };

    class ComponentRegisterationMap
    {

    };
}