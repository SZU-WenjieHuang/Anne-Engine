// 暂时定义一个空的接口头文件

#pragma once
#include "Engine/Core/Singleton.hpp"
#include "Engine/Core/SubSystem.hpp"
#include "Third/entt/entt.hpp"
#include <iostream>

namespace AnneEngine
{
    class ComponentSerilizationMap
    {

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